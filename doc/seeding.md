Seeding and Reading  {#flx_seeding}
===================================

The algebra of @ref flx_algebra returns every derivative of an evaluation at once. Which argument
each of them differentiates is decided when the arguments are seeded.

# Assigning units to arguments {#flx_assignment}

Seeding a value is adding units to it. The argument a unit is given to is written in the call, and
two forms write it. `flx::variable<Ord>` gives every unit of the order to a single value, and
`flx::variables<Is...>` spreads the units of a call over its arguments:

```cpp
auto x        = flx::variable<2>(2.5);
auto [ u, v ] = flx::variables<0, 1>(2.5, -1.0);
auto [ p, q ] = flx::variables<0, 0, 1>(2.5, -1.0);
```

| Result | Type | Value it holds |
|--------|------|----------------|
| `x` | `flx::hyperdual<double,2>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ |
| `u`, `v` | `flx::hyperdual<double,2>` | \f$2.5 + \varepsilon_1\f$ and \f$-1 + \varepsilon_2\f$ |
| `p`, `q` | `flx::hyperdual<double,3>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ and \f$-1 + \varepsilon_3\f$ |

The template list `Is...` holds one entry per unit, in unit order: its \f$i\f$-th entry is the index
of the argument \f$\varepsilon_i\f$ is given to, arguments being counted from zero and units from
one. Its length is the order every seeded result comes back at. The third call above gives units 1
and 2 to the first argument and unit 3 to the second, hence an order 3 on both.

An argument that is given no unit comes back unchanged, at its own type, so the result of a call to
`flx::variables` feeds the function straight through `kumi::apply`.

# Taylor identity {#flx_taylor}

Substituting a nilpotent into an analytic function turns its series into a sum with finitely many
terms, since every monomial of degree \f$n+1\f$ in the units vanishes. That truncation is an
identity, and no approximation.

For a function \f$f\f$ of \f$m\f$ arguments, seed argument \f$j\f$ with the units of a set
\f$U_j\f$, the sets \f$U_1, \dots, U_m\f$ partitioning \f$\{1,\dots,n\}\f$:

\f[ x_j = a_j + \sum_{i \in U_j} \varepsilon_i. \f]

Each unit then belongs to exactly one argument, and \f$k\f$ denotes the map reading that assignment
back, \f$k(i) = j\f$ for the single \f$j\f$ with \f$i \in U_j\f$. It is the list `Is...` of the
previous section. The evaluation gives

\f[ f(x_1,\dots,x_m) = \sum_{S \subseteq \{1,\dots,n\}}
    \left(\frac{\partial^{|S|} f}{\prod_{i \in S} \partial x_{k(i)}}(a_1,\dots,a_m)\right)
    \varepsilon_S. \f]

Every component of the result is a partial derivative of \f$f\f$ at the point, and it carries no
factorial: each unit appears to the first power, so the coefficient of \f$\varepsilon_S\f$ is the
derivative itself.

# Reading a result {#flx_landing}

A component is indexed by the units it carries, as @ref flx_components states. With the seeding
`flx::variables<0, 1>(x, y)` and \f$f\f$ evaluated on the pair, the four components hold

| Component | Units | What it holds |
|:---------:|-------|---------------|
| `get<0>` | none | \f$f(x, y)\f$ |
| `get<1>` | \f$\varepsilon_1\f$ | \f$\partial f/\partial x\f$ |
| `get<2>` | \f$\varepsilon_2\f$ | \f$\partial f/\partial y\f$ |
| `get<3>` | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x\,\partial y\f$ |

One evaluation returns the gradient and the mixed second derivative. Absent from it is
\f$\partial^2 f/\partial x^2\f$: a second derivative in one argument needs two units on that
argument, which `flx::variables<0, 0>` asks for.

Two units per argument gives the square terms as well. Seeding two arguments that way costs order 4
and returns, in a single evaluation, the value, both first derivatives and the whole Hessian:

```cpp
auto [ x, y ] = flx::variables<0, 0, 1, 1>(2.5, -1.0);
```

| Component | Units | What it holds |
|:---------:|-------|---------------|
| `get<1>`  | \f$\varepsilon_1\f$ | \f$\partial f/\partial x\f$ |
| `get<3>`  | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x^2\f$ |
| `get<5>`  | \f$\varepsilon_1\varepsilon_3\f$ | \f$\partial^2 f/\partial x\,\partial y\f$ |
| `get<12>` | \f$\varepsilon_3\varepsilon_4\f$ | \f$\partial^2 f/\partial y^2\f$ |

Several components hold the same derivative, \f$\varepsilon_2\varepsilon_3\f$ answering
\f$\partial^2 f/\partial x\,\partial y\f$ as \f$\varepsilon_1\varepsilon_3\f$ does. A symmetric
object stored as a full set of subsets repeats itself, and that repetition is what caps the useful
order at four.

# Cost of an order {#flx_cost}

An order \f$n\f$ carries \f$2^n\f$ components, so a single value of order 4 weighs sixteen `double`,
and every operation of the arithmetic works on all of them. Two ways of spending that budget answer
different questions.

  + **One unit per argument.** Order \f$m\f$ over \f$m\f$ arguments returns the gradient and every
    mixed partial up to the one of order \f$m\f$, in one evaluation, and never a repeated
    derivative.
  + **Several units per argument.** Order \f$n\f$ over one argument returns
    \f$f', f'', \dots, f^{(n)}\f$ of that argument in one evaluation, and says nothing of the
    others.

A full Hessian of \f$m\f$ arguments therefore comes out of one pass only when \f$2m \le 4\f$. Past
two arguments it is a sweep of \f$m(m+1)/2\f$ evaluations at order 2, one per pair, which is the
usual shape of a forward mode.

# Mixed orders {#flx_mixing}

An operand of order 2 carries nothing of a third derivative, and filling it with zeros would state
that the third derivative vanishes. A mixed expression therefore computes at the **smallest** order
present, and the extra components of the others are dropped. `flx::restrict_to<Ord>` performs that
descent explicitly, on the scalar form as on the wide one.

Only a lone scalar adapts to what it is mixed with. Everything that carries a structure states its
own element type, and two operands stating different ones have no common type at all, which is a
refusal rather than an arbitration.

# Several points at once {#flx_wide}

A component may be a SIMD register rather than a scalar, and the construction goes through
unchanged. `eve::wide<flx::hyperdual<double,2>>` is a structure of arrays holding as many hyperduals
as the machine has lanes, and seeding a wide value seeds every lane, so one evaluation returns the
derivatives at as many points as there are lanes.

This is a different axis from the order. The order says how many derivatives one point carries, the
cardinal how many points travel together, and each is read where it is written: the order from the
element type, the cardinal from `eve::cardinal_v`. Two operands that are genuinely wide have to
agree on their number of lanes.

<div class="section_buttons">

| Previous                          |                              Next |
|:----------------------------------|----------------------------------:|
| [Hyperdual Algebra](@ref flx_algebra) | [Examples](@ref flx_examples) |

</div>
