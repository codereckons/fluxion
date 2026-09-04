Asking For Derivatives, and Reading Them Back  {#derivatives_background}
========================================================================

The algebra of @ref math_background says that evaluating a function on seeded arguments returns
every derivative at once. This page says which derivative lands where, and what an order buys.

# Seeding names what is differentiated

A unit belongs to one argument, and the assignment is written, never guessed. `flx::variable` seeds
a single value with every unit of its order, and `flx::variables` distributes the units of a call
over its arguments, one index per unit:

@code
auto x         = flx::variable<2>(2.5);            // both units to one value
auto [ u, v ]  = flx::variables<0, 1>(2.5, -1.0);  // unit 1 to the first, unit 2 to the second
auto [ p, q ]  = flx::variables<0, 0, 1>(2.5, -1.0);
@endcode

The list is the assignment \f$k(i)\f$ of @ref math_background, its length being the order and its
\f$i\f$-th entry the argument that unit \f$i\f$ is given to. The third line above spends two units
on the first argument and one on the second, so the result is of order 3.

An argument no unit was given to is passed through unchanged, at its own type. Nothing is
differentiated by accident.

# Where each derivative lands

A component is indexed by the units it carries, so with the seeding
`flx::variables<0, 1>(x, y)` and \f$f\f$ evaluated on the pair, the four components read

| Component | Units | What it holds |
|:---------:|-------|---------------|
| `get<0>` | none | \f$f(x, y)\f$ |
| `get<1>` | \f$\varepsilon_1\f$ | \f$\partial f/\partial x\f$ |
| `get<2>` | \f$\varepsilon_2\f$ | \f$\partial f/\partial y\f$ |
| `get<3>` | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x\,\partial y\f$ |

One evaluation, a gradient and a mixed second derivative. What it does not hold is
\f$\partial^2 f/\partial x^2\f$: a second derivative in one variable needs two units on that
variable, which is what `flx::variables<0, 0>` asks for.

Two units per argument gives the square terms as well. Seeding two arguments that way costs order
4 and yields, in a single evaluation, the value, both first derivatives, and the whole Hessian:

@code
auto [ x, y ] = flx::variables<0, 0, 1, 1>(2.5, -1.0);
@endcode

| Component | Units | What it holds |
|:---------:|-------|---------------|
| `get<1>`  | \f$\varepsilon_1\f$ | \f$\partial f/\partial x\f$ |
| `get<3>`  | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x^2\f$ |
| `get<5>`  | \f$\varepsilon_1\varepsilon_3\f$ | \f$\partial^2 f/\partial x\,\partial y\f$ |
| `get<12>` | \f$\varepsilon_3\varepsilon_4\f$ | \f$\partial^2 f/\partial y^2\f$ |

Several components hold the same derivative, \f$\varepsilon_2\varepsilon_3\f$ answering
\f$\partial^2 f/\partial x\,\partial y\f$ as \f$\varepsilon_1\varepsilon_3\f$ does. That is the
price of a symmetric object stored as a full set of subsets, and it is what caps the useful order:
each order doubles the storage, and `flx::max_order` is 4.

# What an order costs

An order \f$n\f$ carries \f$2^n\f$ components, so a single value of order 4 weighs sixteen
`double`. Beyond the memory, every operation of the arithmetic works on all of them.

Two ways of spending that budget answer different questions.

  + **One unit per argument.** Order \f$m\f$ over \f$m\f$ arguments returns the gradient and every
    *mixed* partial, up to the one of order \f$m\f$, in one evaluation. It never returns a repeated
    derivative.
  + **Several units per argument.** Order \f$n\f$ over one argument returns
    \f$f', f'', \dots, f^{(n)}\f$ of that argument in one evaluation, and says nothing of the
    others.

A full Hessian of \f$m\f$ arguments therefore does not come out of one pass unless \f$2m \le 4\f$.
Past two arguments it is a sweep of \f$m(m+1)/2\f$ evaluations at order 2, one per pair, which is
the usual shape of a forward mode.

# Several points at once

A component may be a SIMD register rather than a scalar, and the whole construction goes through
unchanged: `eve::wide<flx::hyperdual<double, 2>>` is a structure of arrays holding as many
hyperduals as the machine has lanes. Seeding a wide value seeds every lane, so one evaluation
returns the derivatives at as many points as there are lanes.

This is a different axis from the order: the order says how many derivatives a point carries, the
cardinal says how many points travel together. Mixing them is the business of the type computation,
which reads the element type and the cardinal each where it is written.

# Meeting values of different orders

An operand of order 2 carries nothing of a third derivative. Filling one with zeros would assert
that it vanishes, which is a statement about the function and not a convention, so a mixed
expression computes at the **smallest** order present, and the extra components of the others are
dropped. `flx::restrict_to<Ord>` performs that descent explicitly, on the scalar form as on the
wide one. Going up is absent by design.
