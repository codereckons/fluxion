Seeding and Reading  {#flx_seeding}
===================================

An evaluation on hyperduals returns all the derivatives it carries at once, and the seeding of the
arguments fixes the argument each of them is taken with respect to.

Three calls seed a value:

  + `flx::variables`, over the arguments of a call;
  + `flx::variable`, over a single value;
  + the constructor `hyperdual<T, Ord>{v, flx::var}`, which builds what `flx::variable` returns.

No other operation seeds: an operation on seeded elements propagates their units, and an element
built from a tuple takes the components written in it.

# Differentiation list {#flx_assignment}

`flx::variables<Is...>(xs...)` takes the list of the differentiations requested: one entry per
differentiation, each naming the argument to differentiate with respect to, arguments being numbered
from zero. `flx::variables<0, 0, 1>(x, y)` therefore requests two differentiations in `x` and one in
`y`. `flx::variable<Ord>(v)` is the one-argument form, with `Ord` differentiations in `v`.

```cpp
auto x        = flx::variable<2>(2.5);              // twice in x
auto [ u, v ] = flx::variables<0, 1>(2.5, -1.0);    // once in u, once in v
auto [ p, q ] = flx::variables<0, 0, 1>(2.5, -1.0); // twice in p, once in q
```

The list holds at most `flx::max_order` entries, four, and each entry names an argument of the call:
`flx::variables<0, 0, 1>(2.5)` names a second argument the call does not have, and does not compile.

Seeding writes that list into the values. For `Is...` \f$= (i_0, \dots, i_{n-1})\f$, argument
\f$j\f$ of value \f$a_j\f$ is seeded as

\f[ x_j = a_j + \sum_{k\,:\,i_k = j} \varepsilon_{k+1}, \f]

each unit belonging to exactly one argument and every seeded result having order \f$n\f$:

| Result | Type | Element | Components, in index order |
|--------|------|----------------|----------------------------|
| `x` | `hyperdual<double,2>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ | 2.5, 1, 1, 0 |
| `u` | `hyperdual<double,2>` | \f$2.5 + \varepsilon_1\f$ | 2.5, 1, 0, 0 |
| `v` | `hyperdual<double,2>` | \f$-1 + \varepsilon_2\f$ | -1, 0, 1, 0 |
| `p` | `hyperdual<double,3>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ | 2.5, 1, 1, 0, 0, 0, 0, 0 |
| `q` | `hyperdual<double,3>` | \f$-1 + \varepsilon_3\f$ | -1, 0, 0, 0, 1, 0, 0, 0 |

Streaming one prints those components with their names, `std::cout << u` giving
`2.5 + 1e1 + 0e2 + 0e12`.

Units are numbered as @ref flx_components numbers them: \f$\varepsilon_u\f$ is stored at bit
\f$u-1\f$.

`flx::variables` returns a `kumi::tuple` with one entry per argument, in the order they were passed,
and the entries need not share a type: an argument named in the list is returned as a
`flx::hyperdual` seeded on its units; one never named is returned unchanged.

```cpp
flx::variables<0, 1>(2.5, -1.0);   // kumi::tuple<hyperdual<double,2>, hyperdual<double,2>>
flx::variables<0>(2.5, -1.0);      // kumi::tuple<hyperdual<double,1>, double>
```

The tuple therefore stands for the argument list, and the call is made through `kumi::apply`:

```cpp
auto vars = flx::variables<0, 1>(2.5, -1.0);
auto r    = kumi::apply(f, vars);                // f(2.5 + e1, -1 + e2)
```

# Taylor identity {#flx_taylor}

Once the arguments are seeded, the content of each component after the evaluation follows from one
identity. Substituting a nilpotent into an analytic function turns its series into a sum with
finitely many terms, since every monomial of degree \f$n+1\f$ or more in the units vanishes, and
that truncation is an identity rather than an approximation.

Evaluating \f$f\f$ on the arguments seeded by that list, where unit \f$u\f$ belongs to argument
\f$i_{u-1}\f$, gives

\f[ f(x_1,\dots,x_m) = \sum_{S \subseteq \{1,\dots,n\}}
    \left(\frac{\partial^{|S|} f}{\prod_{u \in S} \partial x_{i_{u-1}}}(a_1,\dots,a_m)\right)
    \varepsilon_S. \f]

Every component of the result is a partial derivative of \f$f\f$ at the point, and it carries no
factorial: each unit appears to the first power, so the coefficient of \f$\varepsilon_S\f$ is the
derivative itself.

# Reading a result {#flx_landing}

The Taylor identity attaches the derivative indexed by \f$S\f$ to \f$\varepsilon_S\f$, and
\f$\varepsilon_S\f$ is stored at the component of index \f$\sum_{u \in S} 2^{u-1}\f$. Reading a
derivative is therefore one `flx::get` at that index, and writing the index in binary shows the
units it carries. For \f$f(x, y) = x^2 y\f$ at \f$(2.5, -1)\f$, with one differentiation in each
argument:

```cpp
auto f    = [](auto a, auto b) { return a * a * b; };
auto vars = flx::variables<0, 1>(2.5, -1.0);
auto z    = kumi::apply(f, vars);
```

| Component | Units | What it holds | Value |
|:---------:|-------|---------------|------:|
| `flx::get<0b00>(z)` | none | \f$f(x, y)\f$ | -6.25 |
| `flx::get<0b01>(z)` | \f$\varepsilon_1\f$ | \f$\partial f/\partial x = 2xy\f$ | -5 |
| `flx::get<0b10>(z)` | \f$\varepsilon_2\f$ | \f$\partial f/\partial y = x^2\f$ | 6.25 |
| `flx::get<0b11>(z)` | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x\,\partial y = 2x\f$ | 5 |

One evaluation returns the gradient and the mixed second derivative. The result does not contain
\f$\partial^2 f/\partial x^2\f$: a second derivative in one argument needs two units on that
argument, which `flx::variables<0, 0>` provides.

Two differentiations per argument give the square terms as well. For two arguments, this requires
order 4 and returns, in a single evaluation, the value, both first derivatives, and the whole
Hessian. On the same \f$f\f$ and the same point:

```cpp
auto vars = flx::variables<0, 0, 1, 1>(2.5, -1.0);
auto z    = kumi::apply(f, vars);
```

| Component | Units | What it holds | Value |
|:---------:|-------|---------------|------:|
| `flx::get<0b0001>(z)` | \f$\varepsilon_1\f$ | \f$\partial f/\partial x = 2xy\f$ | -5 |
| `flx::get<0b0011>(z)` | \f$\varepsilon_1\varepsilon_2\f$ | \f$\partial^2 f/\partial x^2 = 2y\f$ | -2 |
| `flx::get<0b0101>(z)` | \f$\varepsilon_1\varepsilon_3\f$ | \f$\partial^2 f/\partial x\,\partial y = 2x\f$ | 5 |
| `flx::get<0b1100>(z)` | \f$\varepsilon_3\varepsilon_4\f$ | \f$\partial^2 f/\partial y^2 = 0\f$ | 0 |

Several components hold the same derivative: \f$\varepsilon_1\varepsilon_3\f$ and
\f$\varepsilon_2\varepsilon_3\f$ both hold \f$\partial^2 f/\partial x\,\partial y\f$.

# Cost of an order {#flx_cost}

An element of order \f$n\f$ has \f$2^n\f$ components, so a single element of order 4 occupies
sixteen `double`s, and every operation of the arithmetic works on all of them. An order is used in
one of two ways.

  + **One unit per argument.** Order \f$m\f$ over \f$m\f$ arguments returns the gradient and every
      mixed partial up to the one of order \f$m\f$, in one evaluation, and no repeated derivative.
  + **Several units per argument.** Order \f$n\f$ over one argument returns
    \f$f', f'', \dots, f^{(n)}\f$ of that argument in one evaluation, and no derivative in the
    others.

A full Hessian in \f$m\f$ arguments therefore takes a single pass only when \f$2m \le 4\f$. Past two
arguments it takes a sweep of one of two kinds:

  + at order 2, one evaluation per pair, \f$m(m+1)/2\f$ of them, the pairs \f$(i, i)\f$ giving the
    square terms;
  + at order 4, two units on each argument of a pair, \f$m(m-1)/2\f$ evaluations, each returning
    both square terms and the mixed one.

# Mixed orders {#flx_mixing}

An operand of order 2 carries no third derivative, and filling it with zeros would state that the
third derivative vanishes. A mixed expression therefore computes at the **smallest** order present,
and the extra components of the others are dropped. `flx::restrict_to<Ord>` performs that reduction
explicitly, on the scalar form and on the wide one alike.

Only a plain scalar converts to the type it is mixed with. A hyperdual or a wide fixes its element
type, and two operands with different element types have no common type: mixing them does not
compile.

# Evaluation on SIMD registers {#flx_wide}

A component may be a SIMD register rather than a scalar, and the construction is unchanged.
`eve::wide<flx::hyperdual<double,2>>` is a structure of arrays holding as many hyperduals as the
machine has lanes, and seeding a wide value seeds every lane, so one evaluation returns the
derivatives at as many points as there are lanes.

The cardinal is independent of the order: the order counts the derivatives carried at one point, the
cardinal the points evaluated together. The order is read from the element type, the cardinal from
`eve::cardinal_v`, and two wide operands must have the same number of lanes.

<div class="section_buttons">

| Previous                          |                              Next |
|:----------------------------------|----------------------------------:|
| [Hyperdual Algebra](@ref flx_algebra) | [Examples](@ref flx_examples) |

</div>
