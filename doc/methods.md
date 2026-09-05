Obtaining a Derivative  {#flx_methods}
======================================

Four methods answer the question @ref flx_derivation ends on: by what means is a derivative carried
through an execution. They differ in what they are exact about, what they cost, and what they demand
of the code. They come below in order, from the one that differentiates a formula to the one that
evaluates the function twice and subtracts.

# Symbolic differentiation {#flx_symbolic}

Differentiating the formula gives an exact expression, and evaluating it gives an exact value. It
requires a formula: a program with a loop, a branch or a call into a library is not one. It also
forms the composed expression that @ref flx_rules avoids, and repeated differentiation makes that
expression grow, each order multiplying the number of terms.

# Automatic differentiation {#flx_automatic}

Both modes apply the chain rule to the sequence of operations the program actually performed, so
both are exact to the representation.

  + **Forward mode**, what **FLUXION** implements, carries the derivatives alongside the value. The
    cost of one evaluation is proportional to the number of components carried, and nothing is
    stored between evaluations. A gradient of \f$m\f$ arguments costs a number of passes growing
    with \f$m\f$.
  + **Reverse mode** records the operations of one evaluation, then walks the record backwards. A
    gradient of \f$m\f$ arguments costs one forward pass and one backward pass whatever \f$m\f$ is,
    and the record grows with the number of operations executed.

Each answers a different shape of problem. Forward mode suits few arguments or high orders, reverse
mode a single output differentiated against many parameters at once.

# Complex step {#flx_complex}

Lyness and Moler noted in 1967, and Squire and Trapp made known in 1998, that
\f$\Im\big(f(a + ih)\big)/h\f$ approximates \f$f'(a)\f$ with no subtraction of nearby values. The
cancellation disappears, \f$h\f$ may be taken as small as the representation allows, and the first
derivative comes back to full precision.

Beyond the first derivative it gives nothing, and it asks a great deal of the code.

  + The second derivative comes back entangled with the first.
  + The function has to be analytic.
  + Its implementation has to accept complex arguments and stay analytic through every branch it
    takes.

# Difference quotient {#flx_quotient}

Evaluating \f$\big(f(a+h) - f(a)\big)/h\f$ for a small \f$h\f$ is wrong twice over. The quotient
omits a term of order \f$h\f$, and the subtraction of two nearby values loses digits in proportion
to \f$u/h\f$, with \f$u\f$ the unit roundoff. The two errors move in opposite directions, so the
best \f$h\f$ is a compromise, around \f$\sqrt{u}\f$ for a forward difference, which leaves about
half of the available digits. A central difference improves the truncation and leaves the
cancellation where it was, and a second derivative divides by \f$h^2\f$ and keeps roughly a third of
them.

None of this is a defect of an implementation. The choice of \f$h\f$ is itself the error, and no
care recovers the digits the subtraction has already spent. This is also the only method that
ignores the chain rule: it replays the whole program beside itself and reads the difference.

# Comparison {#flx_summary}

| Method | Exactness | Orders | What it needs |
|--------|-----------|:------:|---------------|
| Symbolic | full | any, with expression growth | a formula |
| Forward mode | full | any, at \f$2^n\f$ components | the program, and a type it accepts |
| Reverse mode | full | first, higher by nesting | the program, and a record of its execution |
| Complex step | full | first only | an analytic function, and complex arithmetic |
| Difference quotient | half the digits, at best | any, degrading fast | nothing |

| Method | In the library |
|--------|----------------|
| Symbolic differentiation | Planned as a second layer: an expression carrying its own derivative as another expression, differentiated once and evaluated as often as wanted. |
| Forward mode | Yes, and it is the whole of the library: hyperduals up to order 4, on scalars as on SIMD registers. |
| Reverse mode | No. It answers the other shape of problem and is a design of its own. |
| Complex step | No. The nilpotent units remove the step at any order, where this removes it at the first. |
| Difference quotient | No. It approximates what an arithmetic carries exactly. |

Forward mode is therefore the whole of the library, and @ref flx_algebra is the arithmetic it
carries its derivatives in.

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
