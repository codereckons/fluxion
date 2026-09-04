Mathematics of Generalized Hyperdual Numbers  {#math_background}
================================================================

# Rationale

Adjoin to the reals a symbol \f$\varepsilon\f$ that is not zero and whose square is, and the pair
\f$a + b\varepsilon\f$ obeys an arithmetic of its own. Clifford introduced it in 1873 as the
*dual numbers*. Its interest for computation is a single identity: for a function \f$f\f$ built
from the arithmetic operations and the usual elementary functions,

\f[ f(a + \varepsilon) = f(a) + f'(a)\,\varepsilon. \f]

The derivative is not estimated here, it is carried. There is no step to choose, no difference of
two nearby numbers to lose digits to, and the coefficient of \f$\varepsilon\f$ is the derivative to
the last bit the representation holds.

One \f$\varepsilon\f$ gives one derivative. **FLUXION** takes several, which is what makes the
construction *generalized*: with \f$n\f$ of them, one evaluation carries every derivative up to
order \f$n\f$, mixed ones included.

# The algebra

Let the *nilpotent units* \f$\varepsilon_1, \dots, \varepsilon_n\f$ commute with each other and
with the reals, and let each square to zero. The algebra they generate is

\f[ \mathcal{H}_n = \mathbb{R}[\varepsilon_1,\dots,\varepsilon_n] \big/
    \left(\varepsilon_i\varepsilon_j - \varepsilon_j\varepsilon_i,\ \varepsilon_i^2\right), \f]

a Weil algebra, the \f$n\f$-fold tensor power of \f$\mathbb{R}[\varepsilon]/(\varepsilon^2)\f$. A
product of distinct units is not zero: what is zero is any product in which a unit appears twice.
The surviving products are therefore indexed by the subsets of \f$\{1,\dots,n\}\f$. Writing
\f$\varepsilon_S = \prod_{i \in S} \varepsilon_i\f$ for a subset \f$S\f$, the basis is
\f$(\varepsilon_S)_{S \subseteq \{1,\dots,n\}}\f$, the dimension is \f$2^n\f$, and the whole
product is

\f[ \varepsilon_S\,\varepsilon_T =
    \begin{cases} \varepsilon_{S \cup T} & \text{if } S \cap T = \varnothing, \\
                  0 & \text{otherwise.} \end{cases} \f]

An element is written \f$z = \sum_S z_S\,\varepsilon_S\f$, with \f$z_\varnothing\f$ its *value*,
the real part under the name the library gives it, and the rest its *nilpotent part*. **FLUXION** calls \f$n\f$ the **order**, carries it in the type as
`flx::hyperdual<T, Ord>`, and stops at `flx::max_order`, which is 4.

| Order | Components | Basis |
|:-----:|:----------:|-------|
| 1 | 2  | \f$1,\ \varepsilon_1\f$ |
| 2 | 4  | \f$1,\ \varepsilon_1,\ \varepsilon_2,\ \varepsilon_1\varepsilon_2\f$ |
| 3 | 8  | the subsets of three units |
| 4 | 16 | the subsets of four units |

Three properties of \f$\mathcal{H}_n\f$ govern what the library can offer.

**It is commutative and associative.** Nothing of that is given up as the order grows: an expression
means what it is written to mean at order 4 as much as at order 1, and no parenthesis has to be
watched. What grows is the size, doubling with each order.

**It is not a division algebra.** Every element whose value is zero is nilpotent, hence a zero
divisor. An element is invertible exactly when its value is, and its inverse is then a finite sum,
the nilpotent part \f$N\f$ satisfying \f$N^{n+1} = 0\f$:

\f[ \frac{1}{a + N} = \frac{1}{a}\sum_{k=0}^{n} \left(\frac{-N}{a}\right)^{k}. \f]

**It carries no order relation.** An ordered ring has no nilpotent element other than zero: were
\f$\varepsilon > 0\f$, squaring would give \f$0 > 0\f$. Comparison of two hyperduals is therefore a
comparison of their values, and never of the derivatives they carry.

# Taylor's series, and why it stops

Substituting a nilpotent into an analytic function turns its series into a sum with finitely many
terms, since every monomial of degree \f$n+1\f$ in the units vanishes. That truncation is not an
approximation, it is an identity. For a function \f$f\f$ of \f$m\f$ arguments, seed argument
\f$k\f$ with the units of a set \f$U_k\f$, the sets \f$U_1, \dots, U_m\f$ partitioning
\f$\{1,\dots,n\}\f$:

\f[ x_k = a_k + \sum_{i \in U_k} \varepsilon_i. \f]

Then

\f[ f(x_1,\dots,x_m) = \sum_{S \subseteq \{1,\dots,n\}}
    \left(\frac{\partial^{|S|} f}{\prod_{i \in S} \partial x_{k(i)}}(a_1,\dots,a_m)\right)
    \varepsilon_S, \f]

where \f$k(i)\f$ names the argument unit \f$i\f$ was given to. Every component of the result is a
partial derivative of \f$f\f$ at the point, and it carries no factorial: each unit appears to the
first power, so the coefficient of \f$\varepsilon_S\f$ is the derivative itself, ready to be read.

This is the whole of the library's contract. What remains is bookkeeping: which unit belongs to
which argument, which component holds which derivative, and how two values of different orders
meet.

# Notation

A component is named by the units it carries, so \f$\varepsilon_1\varepsilon_2\f$ is the component
`e12` on output, and the value is unnamed. Internally, a component index is a bit set: bit
\f$i\f$ of the index says the component carries \f$\varepsilon_{i+1}\f$, so
`get<0>` is the value, `get<1>` the coefficient of \f$\varepsilon_1\f$, and `get<3>` that of
\f$\varepsilon_1\varepsilon_2\f$.

That layout is what makes an order a prefix of the next: the first \f$2^k\f$ components are exactly
the subsets of the first \f$k\f$ units, so an order 2 read out of an order 3 is the first four
components, unchanged. `flx::restrict_to` is that extraction, and it is exact.

The construction is carried over the IEEE `float` and `double` representations of the reals. As
**FLUXION** is built upon EVE, a component may equally be a SIMD register of such values, which is
what `eve::wide<flx::hyperdual<T, Ord>>` is: one hyperdual per lane, stored as a structure of
arrays.

# The library's response

| Mathematical fact | Its expression in the API |
|-------------------|---------------------------|
| The coefficient of \f$\varepsilon_S\f$ is a mixed partial of the arguments the units belong to | `flx::variables<Is...>` names that assignment, one entry per unit |
| A subset of the units gives a smaller algebra, sitting in the first components | `flx::restrict_to<Ord>` extracts, it does not round |
| An operand of order 2 knows nothing of a third derivative | A mixed pack computes at the *smallest* order present, never the largest |
| Nothing distinguishes an unset derivative from a derivative that is zero | A hyperdual is filled exactly: no partial list, no completion by zeros |
| No compatible order relation exists | Comparison reads the value, and the components are read by name |

# References

  + W. K. Clifford, *Preliminary Sketch of Biquaternions*, Proceedings of the London Mathematical
    Society, s1-4, 381-395, where the dual numbers appear. The volume is dated 1871 by the
    publisher and cited as 1873 nearly everywhere else.
    [doi:10.1112/plms/s1-4.1.381](https://doi.org/10.1112/plms/s1-4.1.381)
  + J. A. Fike and J. J. Alonso, *The Development of Hyper-Dual Numbers for Exact Second-Derivative
    Calculations*, AIAA 2011-886, 49th AIAA Aerospace Sciences Meeting, 2011, which adds the second
    unit and the cross term. [doi:10.2514/6.2011-886](https://doi.org/10.2514/6.2011-886)
  + M. Neuenhofen, *Review of Theory and Implementation of Hyper-Dual Numbers for First and Second
    Order Automatic Differentiation*, arXiv:1801.03614, 2018, which covers the same ground and is
    freely readable. [arxiv.org/abs/1801.03614](https://arxiv.org/abs/1801.03614)
  + A. Griewank and A. Walther, *Evaluating Derivatives: Principles and Techniques of Algorithmic
    Differentiation*, SIAM, second edition, 2008, for the vocabulary of the forward mode and its
    seeding. [doi:10.1137/1.9780898717761](https://doi.org/10.1137/1.9780898717761)
