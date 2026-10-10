Seeding and Reading  {#flx_seeding}
===================================

The algebra of @ref flx_algebra "the previous page" returns every derivative of an evaluation at
once. Which argument each of them differentiates is decided when the arguments are seeded.

Three calls seed:

  + `flx::variables`, over the arguments of a call;
  + `flx::variable`, over a single value;
  + the constructor `hyperdual<T, Ord>{v, flx::var}`, which builds what `flx::variable` returns.

Everything else preserves what it is given: an operation on seeded values carries their units
through, and a value built from a tuple takes the components written in it.

# Asking for derivatives {#flx_assignment}

`flx::variables<Is...>(xs...)` takes the list of the derivations wanted: one entry per derivation,
each naming the argument to differentiate against, arguments counting from zero.
`flx::variables<0, 0, 1>(x, y)` therefore asks for two derivations in `x` and one in `y`.
`flx::variable<Ord>(v)` is the one-argument form, `Ord` derivations in `v`.

```cpp
auto x        = flx::variable<2>(2.5);              // twice in x
auto [ u, v ] = flx::variables<0, 1>(2.5, -1.0);    // once in u, once in v
auto [ p, q ] = flx::variables<0, 0, 1>(2.5, -1.0); // twice in p, once in q
```

Two constraints hold on the list: its length \f$n\f$ is at most `flx::max_order`, which is 4, and
every \f$i_k\f$ names an argument of the call. `flx::variables<0, 0, 1>(2.5)` breaks the second and
does not compile.

Seeding writes that list into the values. For `Is...` \f$= (i_0, \dots, i_{n-1})\f$, argument
\f$j\f$ of value \f$a_j\f$ is seeded as

\f[ x_j = a_j + \sum_{k\,:\,i_k = j} \varepsilon_{k+1}, \f]

each unit belonging to exactly one argument and every seeded result having order \f$n\f$:

| Result | Type | Value it holds | Components, in index order |
|--------|------|----------------|----------------------------|
| `x` | `hyperdual<double,2>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ | 2.5, 1, 1, 0 |
| `u` | `hyperdual<double,2>` | \f$2.5 + \varepsilon_1\f$ | 2.5, 1, 0, 0 |
| `v` | `hyperdual<double,2>` | \f$-1 + \varepsilon_2\f$ | -1, 0, 1, 0 |
| `p` | `hyperdual<double,3>` | \f$2.5 + \varepsilon_1 + \varepsilon_2\f$ | 2.5, 1, 1, 0, 0, 0, 0, 0 |
| `q` | `hyperdual<double,3>` | \f$-1 + \varepsilon_3\f$ | -1, 0, 0, 0, 1, 0, 0, 0 |

Streaming one prints those components with their names, `std::cout << u` giving
`2.5 + 1e1 + 0e2 + 0e12`.

Units are numbered as @ref flx_components numbers them: \f$\varepsilon_u\f$ sits in bit
\f$u-1\f$.

`flx::variables` returns a `kumi::tuple` of one entry per argument, in the order they were passed,
and the entries need not share a type: an argument named in the list comes back as a
`flx::hyperdual` seeded on its units, one never named comes back as it was.

```cpp
flx::variables<0, 1>(2.5, -1.0);   // kumi::tuple<hyperdual<double,2>, hyperdual<double,2>>
flx::variables<0>(2.5, -1.0);      // kumi::tuple<hyperdual<double,1>, double>
```

The tuple therefore stands for the argument list, and the call goes through `kumi::apply`:

```cpp
auto vars = flx::variables<0, 1>(2.5, -1.0);
auto r    = kumi::apply(f, vars);                // f(2.5 + e1, -1 + e2)
```

# Taylor identity {#flx_taylor}

Once the arguments are seeded, what the evaluation leaves in each component follows from a single
identity. Substituting a nilpotent into an analytic function turns its series into a sum with
finitely many terms, since every monomial of degree \f$n+1\f$ in the units vanishes, and that
truncation is an identity rather than an approximation.

Evaluating \f$f\f$ on the arguments seeded above, where unit \f$u\f$ belongs to argument
\f$i_{u-1}\f$, gives

\f[ f(x_1,\dots,x_m) = \sum_{S \subseteq \{1,\dots,n\}}
    \left(\frac{\partial^{|S|} f}{\prod_{u \in S} \partial x_{i_{u-1}}}(a_1,\dots,a_m)\right)
    \varepsilon_S. \f]

Every component of the result is a partial derivative of \f$f\f$ at the point, and it carries no
factorial: each unit appears to the first power, so the coefficient of \f$\varepsilon_S\f$ is the
derivative itself.

# Reading a result {#flx_landing}

The identity above puts the derivative indexed by \f$S\f$ on \f$\varepsilon_S\f$, and
\f$\varepsilon_S\f$ is stored at the component of index \f$\sum_{u \in S} 2^{u-1}\f$. Reading a
derivative is therefore one `flx::get` at that index, and writing the index in binary shows the
units it carries. Take \f$f(x, y) = x^2 y\f$ at
\f$(2.5, -1)\f$, one derivation in each argument:

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

One evaluation returns the gradient and the mixed second derivative. Absent from it is
\f$\partial^2 f/\partial x^2\f$: a second derivative in one argument needs two units on that
argument, which `flx::variables<0, 0>` asks for.

Two derivations per argument gives the square terms as well. Asking for that on two arguments costs
order 4 and returns, in a single evaluation, the value, both first derivatives and the whole
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

Several components hold the same derivative, \f$\varepsilon_2\varepsilon_3\f$ answering
\f$\partial^2 f/\partial x\,\partial y\f$ as \f$\varepsilon_1\varepsilon_3\f$ does. A symmetric
object stored as a full set of subsets repeats itself, and that repetition is what caps the useful
order at four.

# Cost of an order {#flx_cost}

An order \f$n\f$ carries \f$2^n\f$ components, so a single value of order 4 weighs sixteen `double`,
and every operation of the arithmetic works on all of them. Two ways of using an order answer
different questions.

  + **One unit per argument.** Order \f$m\f$ over \f$m\f$ arguments returns the gradient and every
    mixed partial up to the one of order \f$m\f$, in one evaluation, and never a repeated
    derivative.
  + **Several units per argument.** Order \f$n\f$ over one argument returns
    \f$f', f'', \dots, f^{(n)}\f$ of that argument in one evaluation, and says nothing of the
    others.

A full Hessian of \f$m\f$ arguments therefore comes out of one pass only when \f$2m \le 4\f$. Past
two arguments it takes a sweep, of one of two kinds:

  + at order 2, one evaluation per pair, \f$m(m+1)/2\f$ of them, the pairs \f$(i, i)\f$ giving the
    square terms;
  + at order 4, two units on each argument of a pair, \f$m(m-1)/2\f$ evaluations, each returning
    both square terms and the mixed one.

# Mixed orders {#flx_mixing}

An operand of order 2 carries nothing of a third derivative, and filling it with zeros would state
that the third derivative vanishes. A mixed expression therefore computes at the **smallest** order
present, and the extra components of the others are dropped. `flx::restrict_to<Ord>` performs that
descent explicitly, on the scalar form as on the wide one.

Only a lone scalar adapts to what it is mixed with. Everything that carries a structure states its
own element type, and two operands stating different ones have no common type: their mix does not
compile.

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
