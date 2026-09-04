What The Other Ways Of Differentiating Cost  {#alternatives_background}
=======================================================================

Four families of methods answer the question *what is the derivative of this program*. They differ
in what they are exact about, what they cost, and what they need of the code.

# A difference quotient

\f$\big(f(a+h) - f(a)\big)/h\f$ is wrong twice over. The quotient itself omits a term of order
\f$h\f$, and the subtraction of two nearby values loses digits in proportion to \f$u/h\f$, with
\f$u\f$ the unit roundoff. The two errors pull in opposite directions, so the best \f$h\f$ is a
compromise: around \f$\sqrt{u}\f$ for a forward difference, which leaves about half of the
available digits. A central difference improves the truncation, not the cancellation, and a second
derivative divides by \f$h^2\f$ and keeps roughly a third of them.

None of it is a defect of the implementation. There is no step to choose well because the choice
itself is the error, and no amount of care recovers the digits the subtraction has already spent.

# The complex step

Lyness and Moler noted in 1967, and Squire and Trapp made known in 1998, that
\f$\Im\big(f(a + ih)\big)/h\f$ approximates \f$f'(a)\f$ with no subtraction of nearby values. The
cancellation disappears, \f$h\f$ may be taken as small as the representation allows, and the first
derivative comes back to full precision.

It stops there. The second derivative comes back entangled with the first, the function has to be
analytic, and its implementation has to accept complex arguments and stay analytic through every
branch it takes. A dual number is the same trick made algebraic, with \f$\varepsilon^2 = 0\f$ in
place of \f$i^2 = -1\f$: nothing to cancel, no \f$h\f$ at all, and the construction extends to
higher orders, which is what Fike and Alonso introduced hyperdual numbers for in 2011.

# Symbolic differentiation

Differentiating the formula gives an exact expression, and evaluating it gives an exact value. It
requires a formula: a program with a loop, a branch or a call into a library is not one. Repeated
differentiation also grows the expression, each order multiplying the number of terms, so the
third derivative of a modest formula is rarely a modest formula.

# Automatic differentiation

Both modes evaluate the program itself and apply the chain rule to it, so both are exact to the
representation.

  + **Forward mode**, what **FLUXION** implements, carries the derivatives alongside the value.
    The cost of one evaluation is proportional to the number of components, \f$2^n\f$ at order
    \f$n\f$, and nothing is stored between evaluations. A gradient of \f$m\f$ arguments costs a
    number of passes growing with \f$m\f$.
  + **Reverse mode** records the operations of one evaluation, then walks the record backwards. A
    gradient of \f$m\f$ arguments costs one forward pass and one backward pass, whatever \f$m\f$
    is, at the price of a record whose size grows with the number of operations executed.

The two are complements rather than competitors: forward mode wins when the arguments are few or
the derivatives are of high order, reverse mode when a scalar is to be differentiated against many
parameters at once.

| Method | Exactness | Orders | What it needs |
|--------|-----------|:------:|---------------|
| Difference quotient | half the digits, at best | any, degrading fast | nothing |
| Complex step | full | first only | an analytic function, and complex arithmetic |
| Symbolic | full | any, with expression growth | a formula |
| Forward mode | full | any, at \f$2^n\f$ components | the program, and a type it accepts |
| Reverse mode | full | first, higher by nesting | the program, and a record of its execution |

# Which of them FLUXION does

| Method | In the library |
|--------|----------------|
| Difference quotient | No, and not by omission: approximating what the arithmetic can carry exactly is the one thing the library exists not to do. |
| Complex step | No. The nilpotent units buy the same freedom from a step, at any order rather than at the first alone. |
| Symbolic differentiation | Planned, as a second layer: an expression that carries its own derivative as another expression, differentiated once and evaluated as often as wanted. This is still in early design phase. |
| Forward mode | Yes, and it is the whole of the library: hyperduals up to order 4, on scalars as on SIMD registers. |
| Reverse mode | No. It answers the other shape of problem, one output against many parameters, and is a design of its own rather than an option of this one. |

# What a program's derivative is

Automatic differentiation returns the derivative of the program that was run, which is the
derivative of the mathematical function only where the two agree. A branch on a comparison, an
absolute value at zero, a table lookup: each returns the derivative of the piece it selected, and
the choice belongs to the code rather than to the library. **FLUXION** carries derivatives through
the arithmetic it is given, faithfully, and asserts nothing about the function behind it.

# References

  + J. N. Lyness and C. B. Moler, *Numerical Differentiation of Analytic Functions*, SIAM Journal on
    Numerical Analysis, 4(2), 202-210, 1967.
    [doi:10.1137/0704019](https://doi.org/10.1137/0704019)
  + W. Squire and G. Trapp, *Using Complex Variables to Estimate Derivatives of Real Functions*,
    SIAM Review, 40(1), 110-112, 1998.
    [doi:10.1137/S003614459631241X](https://doi.org/10.1137/S003614459631241X)
  + A. Griewank and A. Walther, *Evaluating Derivatives: Principles and Techniques of Algorithmic
    Differentiation*, SIAM, second edition, 2008, for both modes and what each costs.
    [doi:10.1137/1.9780898717761](https://doi.org/10.1137/1.9780898717761)
