Hyperdual Algebra  {#flx_algebra}
=================================

@ref flx_methods ends on forward mode, which needs a place to keep a value together with the
derivatives asked of it, and an arithmetic that updates both at every operation. A number carrying
its own derivative is that place.

Clifford's *dual numbers*, of 1873, carry one derivative. Fike and Alonso added a second unit in
2011 and named the result a *hyper-dual* number, the prefix marking the several units as it does for
the hypercomplex numbers built on more than one imaginary unit. **FLUXION** takes \f$n\f$ units
rather than two, which is what *generalized* names here. They form an algebra, and each of its
properties has a name in the library.

# One unit {#flx_one_unit}

Adjoin to the reals a symbol \f$\varepsilon\f$ with \f$\varepsilon \neq 0\f$ and
\f$\varepsilon^2 = 0\f$. An element is a pair \f$a + b\varepsilon\f$, and products close on that
form, since the \f$\varepsilon^2\f$ term vanishes:

\f[ (a + b\varepsilon)(c + d\varepsilon) = ac + (ad + bc)\,\varepsilon. \f]

The coefficient of \f$\varepsilon\f$ obeys the product rule of @ref flx_rules, and for a function
built from the arithmetic operations and the usual elementary functions,

\f[ f(a + \varepsilon) = f(a) + f'(a)\,\varepsilon. \f]

This is the complex step made algebraic, with \f$\varepsilon^2 = 0\f$ in place of
\f$i^2 = -1\f$. No \f$h\f$ has to be chosen and nothing cancels, and the coefficient of
\f$\varepsilon\f$ is the derivative to the last bit the representation holds. In the library such
a number is a type carrying its order:

```cpp
flx::hyperdual<double,1> z{2.5, 1.0};   // 2.5 + e1
```

# Several units {#flx_n_units}

A second unit brings \f$\varepsilon_2\f$, and with it the product
\f$\varepsilon_1\varepsilon_2\f$, which does not vanish since the two units are distinct. That
component is where the second derivative lands. Let
\f$\varepsilon_1, \dots, \varepsilon_n\f$ commute with each other and with the reals, and let each
square to zero. The algebra they generate is

\f[ \mathcal{H}_n = \mathbb{R}[\varepsilon_1,\dots,\varepsilon_n] \big/
    \left(\varepsilon_i\varepsilon_j - \varepsilon_j\varepsilon_i,\ \varepsilon_i^2\right), \f]

a Weil algebra, the \f$n\f$-fold tensor power of \f$\mathbb{R}[\varepsilon]/(\varepsilon^2)\f$. A
product of distinct units is not zero, and any product in which a unit appears twice is. The
surviving products are therefore indexed by the subsets of \f$\{1,\dots,n\}\f$. Writing
\f$\varepsilon_S = \prod_{i \in S} \varepsilon_i\f$, the basis is
\f$(\varepsilon_S)_{S \subseteq \{1,\dots,n\}}\f$, the dimension is \f$2^n\f$, and the product of
two basis elements is

\f[ \varepsilon_S\,\varepsilon_T =
    \begin{cases} \varepsilon_{S \cup T} & \text{if } S \cap T = \emptyset, \\
                  0 & \text{otherwise.} \end{cases} \f]

**FLUXION** calls \f$n\f$ the **order** and carries it in the type. The order is bounded, each one
doubling the number of components stored:

```cpp
flx::hyperdual<double,1> a;      //  2 components: 1, e1
flx::hyperdual<double,2> b;      //  4 components: 1, e1, e2, e12
flx::hyperdual<double,3> c;      //  8 components: the subsets of three units
flx::hyperdual<double,4> d;      // 16 components: the subsets of four units

flx::order_v<decltype(c)>;       // 3
flx::dimension_v<decltype(c)>;   // 8
flx::max_order;                  // 4
```

Four is where **FLUXION** stops. A value of order 4 holds sixteen components, every operation of the
arithmetic works on all of them, and several of them answer the same derivative (see
@ref flx_landing).

# Component indexing {#flx_components}

An element carries one coefficient per subset of the units, and is the sum of them:

\f[ z = \sum_{S \subseteq \{1,\dots,n\}} z_S\,\varepsilon_S
      = z_\emptyset + z_{\{1\}}\varepsilon_1 + \dots + z_{\{1,\dots,n\}}\varepsilon_1\cdots
        \varepsilon_n. \f]

The empty subset multiplies no unit, so \f$z_\emptyset\f$ is the ordinary number the element is
built around, and **FLUXION** calls it the **value**. The other \f$2^n - 1\f$ coefficients form the
**nilpotent part**.

Each coefficient is a component of the stored value, and its index says which units it belongs to,
one bit per unit: bit \f$i\f$ set means the component carries \f$\varepsilon_{i+1}\f$. Index zero
holds the value, and the indices that are powers of two hold the coefficients of the single units.

```cpp
flx::get<0>(z);   // the value
flx::get<1>(z);   // the coefficient of e1
flx::get<3>(z);   // the coefficient of e1 e2, bits 0 and 1 both set
```

Streaming a value prints the same names, the value unnamed and the others suffixed:

```cpp
std::cout << flx::hyperdual<double,2>{1.0, 2.0, 3.0, 4.0};   // 1 + 2e1 + 3e2 + 4e12
```

# Constants and variables {#flx_constants}

A value carrying no nilpotent part is a constant: differentiating anything against it returns zero.
A value carrying a one in front of every unit is a variable, which is what makes derivatives flow
from it.

```cpp
flx::hyperdual<double,2> k{2.5};              // 2.5, a constant
flx::hyperdual<double,2> x{2.5, flx::var};    // 2.5 + e1 + e2, a variable
```

A hyperdual is filled exactly. The three forms above and a tuple of the exact size are the only ways
to build one, a partial list being refused rather than completed:

```cpp
flx::hyperdual<double,2> z{1.0, 2.0, 3.0, 4.0};   // four values for four components
flx::hyperdual<double,2> w{1.0, 2.0};             // refused at compile time
```

@note Completing by zeros would state that the missing derivatives vanish, which is an assertion
about the function rather than a convention about storage.

# Sum, product, and inverse {#flx_arithmetic}

\f$\mathcal{H}_n\f$ is commutative and associative at every order, so an expression means what it is
written to mean at order 4 as much as at order 1, and no parenthesis has to be watched. What grows
is the size, doubling with each order, and every operation works on all of the components.

It is not a division algebra. Every element whose value is zero is nilpotent, hence a zero divisor.
An element is invertible exactly when its value is, and the inverse is then a finite sum, the
nilpotent part \f$N\f$ satisfying \f$N^{n+1} = 0\f$:

\f[ \frac{1}{a + N} = \frac{1}{a}\sum_{k=0}^{n} \left(\frac{-N}{a}\right)^{k}. \f]

Every arithmetic operator and every elementary function applies to a hyperdual and returns one, its
components being those the algebra prescribes:

```cpp
auto s = x + y;         // added component by component
auto p = x * y;         // the product above, unit by unit
auto q = x / y;         // defined exactly when the value of y is
auto e = flx::exp(x);   // the value, and every derivative it carries
```

# No order relation {#flx_order_relation}

An ordered ring has no nilpotent element other than zero: were \f$\varepsilon > 0\f$, squaring would
give \f$0 > 0\f$. No comparison of two hyperduals can therefore extend the comparison of the reals,
and the library compares values:

```cpp
x == y;   // compares the values alone
x <  y;   // absent
```

Reading a derivative is done by component, by name or by index, and never by comparison.

# Lower orders as prefixes {#flx_subalgebra}

The units \f$\varepsilon_1, \dots, \varepsilon_k\f$ generate a subalgebra of \f$\mathcal{H}_n\f$ for
\f$k \le n\f$. The binary layout of the indices places it first: the first \f$2^k\f$ components are
exactly the subsets of the first \f$k\f$ units, so reading an order \f$k\f$ out of an order \f$n\f$
is taking a prefix, component for component.

```cpp
flx::hyperdual<double,4> z;
auto y = flx::restrict_to<2>(z);   // the first four components, unchanged
```

The extraction is exact, and there is nothing that goes the other way: raising an order would fill
components with zeros the operand never held.

# References {#flx_algebra_refs}

  + W. K. Clifford, *Preliminary Sketch of Biquaternions*, Proceedings of the London Mathematical
    Society, s1-4, 381-395, where the dual numbers appear. The volume is dated 1871 by the publisher
    and cited as 1873 nearly everywhere else.
    [doi:10.1112/plms/s1-4.1.381](https://doi.org/10.1112/plms/s1-4.1.381)
  + J. A. Fike and J. J. Alonso, *The Development of Hyper-Dual Numbers for Exact Second-Derivative
    Calculations*, AIAA 2011-886, 49th AIAA Aerospace Sciences Meeting, 2011, which adds the second
    unit and the cross term. [doi:10.2514/6.2011-886](https://doi.org/10.2514/6.2011-886)
  + M. Neuenhofen, *Review of Theory and Implementation of Hyper-Dual Numbers for First and Second
    Order Automatic Differentiation*, arXiv:1801.03614, 2018, which covers the same ground and is
    freely readable. [arxiv.org/abs/1801.03614](https://arxiv.org/abs/1801.03614)

<div class="section_buttons">

| Previous                          |                                  Next |
|:----------------------------------|--------------------------------------:|
| [Obtaining a Derivative](@ref flx_methods) | [Seeding and Reading](@ref flx_seeding) |

</div>
