Obtaining a Derivative  {#flx_methods}
======================================

Five methods answer the question @ref flx_derivation ends on: by what means is a derivative carried
through an execution. They differ in their accuracy, their cost, and what they demand of the code.
They come below in order, from the one that differentiates a formula to the one that evaluates the
function on a complex argument.

# Symbolic differentiation {#flx_symbolic}

Differentiating the formula gives an exact expression, and evaluating it gives an exact value. It
requires a formula: a program with a loop, a branch or a call into a library is not one. It also
forms the composed expression that @ref flx_rules avoids, and repeated differentiation makes that
expression grow, each order multiplying the number of terms.

# Automatic differentiation {#flx_automatic}

Both modes apply the chain rule to the sequence of operations the program actually performed, so
neither has a truncation error: a derivative is rounded as the value it accompanies is.

  + **Forward mode**, what **FLUXION** implements, carries the derivatives alongside the value. The
    cost of one evaluation grows with the number of components carried, and nothing is
    stored between evaluations. A gradient of \f$m\f$ arguments costs a number of passes growing
    with \f$m\f$.
  + **Reverse mode** records the operations of one evaluation, then walks the record backwards. A
    gradient of \f$m\f$ arguments costs one forward pass and one backward pass whatever \f$m\f$ is,
    and the record grows with the number of operations executed.

Forward mode suits few inputs or high orders, reverse mode a single output differentiated against
many inputs.


# Difference quotient {#flx_quotient}

For a small \f$h\f$, the forward difference carries two errors at once:

\f[ \frac{f(a+h) - f(a)}{h} = f'(a) + \frac{h}{2}f''(\xi)
    + O\!\left(\frac{u\,|f(a)|}{h}\right), \f]

with \f$u\f$ the unit roundoff. The truncation grows with \f$h\f$ and the cancellation with
\f$1/h\f$, so their sum is smallest near \f$h = \sqrt{u}\f$, which leaves about half of the
available digits. A central difference improves the truncation and leaves the cancellation where
it was. A second derivative divides by \f$h^2\f$: its central difference keeps about half of the
digits, its one-sided difference about a third.

No choice of \f$h\f$ removes both errors, and the digits the cancellation removes cannot be
restored afterwards.

It is also the only method that ignores the chain rule: it evaluates the program twice and reads
the difference.

# Complex step {#flx_complex}

Lyness and Moler noted in 1967, and Squire and Trapp made known in 1998, that
\f$\Im\big(f(a + ih)\big)/h\f$ approximates \f$f'(a)\f$ with no subtraction of nearby values. The
cancellation disappears, \f$h\f$ may be taken as small as the representation allows, and the first
derivative comes back to full precision.

It reaches the first derivative only, and constrains the code.

  + The second derivative appears only in the real part,
    \f$\Re\big(f(a + ih)\big) = f(a) - \frac{h^2}{2}f''(a) + O(h^4)\f$, and recovering it
    subtracts \f$f(a)\f$: the cancellation comes back.
  + The function has to be real analytic.
  + Its implementation has to accept complex arguments and stay analytic through every branch it
    takes.

# Comparison {#flx_summary}

| Method | Accuracy | Orders | What it needs |
|--------|-----------|:------:|---------------|
| Symbolic | rounding only | any, with expression growth | a formula |
| Forward mode | rounding only | any; \f$2^n\f$ components with hyperduals | the program, and a type it accepts |
| Reverse mode | rounding only | first, higher by nesting | the program, and a record of its execution |
| Difference quotient | half the digits, at best | any, degrading fast | nothing |
| Complex step | rounding only | first only | a real analytic function, and complex arithmetic |

| Method | In the library |
|--------|----------------|
| Symbolic differentiation | Planned as a second layer: an expression carrying its own derivative as another expression, differentiated once and evaluated as often as wanted. |
| Forward mode | Yes, and it is the whole of the library: hyperduals up to order 4, on scalars as on SIMD registers. |
| Reverse mode | No. It serves many inputs and few outputs, and is a design of its own. |
| Complex step | No. The nilpotent units remove the step at any order, where this only removes it at the first. |
| Difference quotient | No. It approximates what an arithmetic method carries exactly. |

# References {#flx_methods_refs}

  + J. N. Lyness and C. B. Moler, *Numerical Differentiation of Analytic Functions*, SIAM Journal on
    Numerical Analysis, 4(2), 202-210, 1967.
    [doi:10.1137/0704019](https://doi.org/10.1137/0704019)
  + W. Squire and G. Trapp, *Using Complex Variables to Estimate Derivatives of Real Functions*,
    SIAM Review, 40(1), 110-112, 1998.
    [doi:10.1137/S003614459631241X](https://doi.org/10.1137/S003614459631241X)
  + A. Griewank and A. Walther, *Evaluating Derivatives: Principles and Techniques of Algorithmic
    Differentiation*, SIAM, second edition, 2008, for both modes and what each costs.
    [doi:10.1137/1.9780898717761](https://doi.org/10.1137/1.9780898717761)

<div class="section_buttons">

| Previous                                  |                              Next |
|:------------------------------------------|----------------------------------:|
| [Differentiating a Program](@ref flx_derivation) | [Hyperdual Algebra](@ref flx_algebra) |

</div>
