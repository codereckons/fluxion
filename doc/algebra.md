Hyperdual Algebra  {#flx_algebra}
=================================

Forward mode needs a type holding a value together with the requested derivatives, and an arithmetic
that updates both at every operation. Clifford's *dual numbers* (1873) carry one derivative. Fike
and Alonso added a second unit in 2011 and named the result a *hyper-dual* number, the prefix
marking the presence of several units, as it does for hypercomplex numbers built on more than one
imaginary unit. **FLUXION** takes \f$n\f$ units in place of two; *generalized* refers to that
extension. The units generate an algebra; the library names its order and, within an element, the
value and the nilpotent part.

# Dual numbers {#flx_one_unit}

Adjoin to the reals a symbol \f$\varepsilon\f$ with \f$\varepsilon \neq 0\f$ and
\f$\varepsilon^2 = 0\f$. That symbol is the **dual unit**, as \f$i\f$ is the imaginary unit of the
complex numbers. An element is a pair \f$a + b\varepsilon\f$, and the product of two such pairs has
the same form, since the \f$\varepsilon^2\f$ term vanishes:

\f[ (a + b\varepsilon)(c + d\varepsilon) = ac + (ad + bc)\,\varepsilon. \f]

The coefficient of \f$\varepsilon\f$ obeys the product rule of @ref flx_rules, and for a function
built from the arithmetic operations and the usual elementary functions,

\f[ f(a + \varepsilon) = f(a) + f'(a)\,\varepsilon. \f]

The construction is that of the complex step, with \f$\varepsilon^2 = 0\f$ in place of
\f$i^2 = -1\f$. No \f$h\f$ has to be chosen, and nothing cancels: the coefficient of
\f$\varepsilon\f$ is the derivative, rounded as the value is. In the library, such a number is an
instance of a type carrying its order:

```cpp
flx::hyperdual<double,1> z{2.5, 1.0};   // 2.5 + e1
```

# Hyperdual numbers {#flx_n_units}

A second unit \f$\varepsilon_2\f$ adds the product \f$\varepsilon_1\varepsilon_2\f$, which does not
vanish since the two units are distinct. Its coefficient holds the second derivative. Let
\f$\varepsilon_1, \dots, \varepsilon_n\f$ commute with each other and with the reals, and let each
square to zero. The algebra they generate is

\f[ \mathcal{H}_n = \mathbb{R}[\varepsilon_1,\dots,\varepsilon_n] \big/
    \left(\varepsilon_1^2,\dots,\varepsilon_n^2\right), \f]

a Weil algebra, the \f$n\f$-fold tensor power of \f$\mathbb{R}[\varepsilon]/(\varepsilon^2)\f$. A
product of distinct units is not zero, and any product in which a unit appears twice is zero. The
nonzero products are therefore indexed by the subsets of \f$\{1,\dots,n\}\f$. With
\f$\varepsilon_S = \prod_{i \in S} \varepsilon_i\f$, the basis is
\f$(\varepsilon_S)_{S \subseteq \{1,\dots,n\}}\f$, the dimension is \f$2^n\f$, and the product of
two basis elements is

\f[ \varepsilon_S\,\varepsilon_T =
    \begin{cases} \varepsilon_{S \cup T} & \text{if } S \cap T = \emptyset, \\
                  0 & \text{otherwise.} \end{cases} \f]

**FLUXION** calls \f$n\f$ the **order** and carries it in the type. The order is bounded, each
increment of it doubling the number of components stored:

```cpp
flx::hyperdual<double,1> a;   // 1, e1
flx::hyperdual<double,2> b;   // 1, e1, e2, e12
flx::hyperdual<double,3> c;   // 1, e1, e2, e12, e3, e13, e23, e123
flx::hyperdual<double,4> d;   // 1, e1, e2, e12, e3, e13, e23, e123, e4, e14, e24, e124, e34, e134, e234, e1234

constexpr unsigned int order     = flx::order_v<decltype(c)>;       // 3
constexpr unsigned int dimension = flx::dimension_v<decltype(c)>;   // 8
constexpr unsigned int cap       = flx::max_order;                  // 4
```

\f$\mathcal{H}_n\f$ is defined for every \f$n\f$, and the bound is the library's: the number of
components doubles at each order, every operation works on all of the components, and past order 4
the compile times become impractical.

# Component indexing {#flx_components}

An element has one coefficient per subset of the units, and is the sum of the corresponding terms:

\f[ z = \sum_{S \subseteq \{1,\dots,n\}} z_S\,\varepsilon_S
      = z_\emptyset + z_{\{1\}}\varepsilon_1 + \dots + z_{\{1,\dots,n\}}\varepsilon_1\cdots
        \varepsilon_n. \f]

The empty subset contributes no unit, so \f$z_\emptyset\f$ is the real part of the element, and
**FLUXION** calls it the **value**. The other \f$2^n - 1\f$ coefficients form the **nilpotent
part**.

Each coefficient is a component of the stored element, and its index encodes the units it carries,
one bit per unit: a set bit \f$i\f$ indicates that the component carries \f$\varepsilon_{i+1}\f$.
Index zero holds the value, and the indices that are powers of two hold the coefficients of the
single units.

```cpp
flx::get<0b00>(z);   // the value
flx::get<0b01>(z);   // the coefficient of e1
flx::get<0b11>(z);   // the coefficient of e1 e2, bits 0 and 1 both set
```

The index is a plain integer, and `flx::get<3>(z)` is the same call; the binary literal shows the
units as its bits.

Streaming an element prints its components with the same unit names, the value bare and each other
component suffixed with its units:

```cpp
std::cout << flx::hyperdual<double,2>{1.0, 2.0, 3.0, 4.0};   // 1 + 2e1 + 3e2 + 4e12
```

# Constants and variables {#flx_constants}

An element carrying no nilpotent part is a constant: differentiating anything with respect to it
returns zero. An element carrying a coefficient of one on every unit is a variable: derivatives are
taken with respect to it.

```cpp
flx::hyperdual<double,2> k{2.5};              // 2.5, a constant
flx::hyperdual<double,2> x{2.5, flx::var};    // 2.5 + e1 + e2, a variable
```

Building a variable is called seeding, and @ref flx_seeding gives the forms that seed the arguments
of a call.

A hyperdual is built from a complete list of components. A single value, a value with `flx::var`,
the full list of components, and a tuple of the same size are the only ways to build one; a partial
list is refused:

```cpp
flx::hyperdual<double,2> z{1.0, 2.0, 3.0, 4.0};   // four values for four components
flx::hyperdual<double,2> w{1.0, 2.0};             // refused at compile time
```

@note Completing with zeros would state that the missing derivatives vanish, which is an assertion
about the function rather than a convention about storage.

# Sum, product, and inverse {#flx_arithmetic}

\f$\mathcal{H}_n\f$ is commutative and associative at every order, so an expression has the same
value in exact arithmetic whatever the sequence of its operations; in floating point, as on the
reals, its rounding still depends on that sequence.

\f$\mathcal{H}_n\f$ is not a division algebra. Every element whose value is zero is nilpotent, hence
a zero divisor. An element is invertible exactly when its value is, and the inverse is then a finite
sum, the nilpotent part \f$N\f$ satisfying \f$N^{n+1} = 0\f$. For a nonzero value \f$a\f$:

\f[ \frac{1}{a + N} = \frac{1}{a}\sum_{k=0}^{n} \left(\frac{-N}{a}\right)^{k}. \f]

Every arithmetic operator and every elementary function applies to a hyperdual and returns one, its
components being those the algebra prescribes:

```cpp
auto s = x + y;         // added component by component
auto p = x * y;         // the product above, unit by unit
auto q = x / y;         // defined exactly when the value of y is not 0
auto e = flx::log(x);   // the value, and every derivative it carries, as soon as x is a variable
```

# Comparison operators {#flx_ordering}

In an ordered ring, \f$x \neq 0\f$ implies \f$x^2 > 0\f$, which \f$\varepsilon_i^2 = 0\f$
contradicts unless \f$\varepsilon_i = 0\f$. No ordering of \f$\mathcal{H}_n\f$ extends that of the
reals, and the library compares the values alone:

```cpp
x == y;   // compares the values alone
x < y;    // compares the values alone
```

# Lower orders as prefixes {#flx_subalgebra}

The units \f$\varepsilon_1, \dots, \varepsilon_k\f$ generate a subalgebra of \f$\mathcal{H}_n\f$ for
\f$k \le n\f$, and the binary layout of the indices stores its components at the lowest indices:

\f[ S \subseteq \{1,\dots,k\} \iff \mathrm{index}(\varepsilon_S) < 2^k. \f]

Reading an element of order \f$k\f$ out of one of order \f$n\f$ therefore takes a prefix of the
components.

```cpp
flx::hyperdual<double,4> z;
auto y = flx::restrict_to<2>(z);   // the first four components, unchanged
```

The extraction is exact. No conversion raises the order: it would fill components with zeros the
operand never held.

# References {#flx_algebra_refs}

  + W. K. Clifford, *Preliminary Sketch of Biquaternions*, Proceedings of the London Mathematical
    Society, s1-4, 381-395, where the dual numbers appear. The volume is dated 1871 by the publisher
    and cited as 1873 nearly everywhere else.
    [doi:10.1112/plms/s1-4.1.381](https://doi.org/10.1112/plms/s1-4.1.381)
  + J. A. Fike and J. J. Alonso, *The Development of Hyper-Dual Numbers for Exact Second-Derivative
    Calculations*, AIAA 2011-886, 49th AIAA Aerospace Sciences Meeting, 2011, which adds the second
    unit and the cross term. [doi:10.2514/6.2011-886](https://doi.org/10.2514/6.2011-886)
  + M. Neuenhofen, *Review of Theory and Implementation of Hyper-Dual Numbers for First and Second
    Order Automatic Differentiation*, arXiv:1801.03614, 2018, a survey of the same material, openly
    available. [arxiv.org/abs/1801.03614](https://arxiv.org/abs/1801.03614)

<div class="section_buttons">

| Previous                          |                                  Next |
|:----------------------------------|--------------------------------------:|
| [Obtaining a Derivative](@ref flx_methods) | [Seeding and Reading](@ref flx_seeding) |

</div>
