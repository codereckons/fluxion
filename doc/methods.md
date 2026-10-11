Obtaining a Derivative  {#flx_methods}
======================================

Five methods compute a derivative. They differ in their accuracy, their cost, and what they require
of the code.

# Symbolic differentiation {#flx_symbolic}

Differentiating a formula gives an exact expression, and evaluating it gives a value exact up to
rounding. It requires a formula: a program with a loop, a branch, or a call into a library is not
one. It also forms the composed expression that @ref flx_rules avoids, and repeated differentiation
makes that expression grow, each order multiplying the number of terms.

# Automatic differentiation {#flx_automatic}

Both modes apply the chain rule to the sequence of operations the program performed, so neither has
a truncation error: a derivative is rounded as the value it accompanies is.

  + **Forward mode**, which **FLUXION** implements, carries the derivatives alongside the value. The
      cost of one evaluation grows with the number of components carried, and nothing is stored
      between evaluations. A gradient with respect to \f$m\f$ arguments requires a number of passes
      that grows with \f$m\f$.
  + **Reverse mode** records the operations of one evaluation, then traverses the record backward. A
      gradient with respect to \f$m\f$ arguments requires one forward pass and one backward pass for
      any \f$m\f$, and the record grows with the number of operations executed.

Forward mode suits few inputs or high orders, reverse mode a single output differentiated with
respect to many inputs.

# Difference quotient {#flx_quotient}

For a small \f$h\f$, the forward difference contains two error terms at once:

\f[ \frac{f(a+h) - f(a)}{h} = f'(a) + \frac{h}{2}f''(\xi)
    + O\!\left(\frac{u\,|f(a)|}{h}\right), \f]

with \f$u\f$ the unit roundoff. The truncation error grows with \f$h\f$ and the cancellation with
\f$1/h\f$, so their sum is smallest near \f$h = \sqrt{u}\f$, which leaves about half of the
available digits. A central difference reduces the truncation error and leaves the cancellation
unchanged. A second derivative divides by \f$h^2\f$: its central difference keeps about half of the
digits, its one-sided difference about a third.

No choice of \f$h\f$ removes both errors, and the digits the cancellation removes cannot be restored
afterward.

The difference quotient is also the only method that does not apply the chain rule: it evaluates the
program twice and takes the difference.

# Complex step {#flx_complex}

Lyness and Moler (1967) and Squire and Trapp (1998) show that \f$\Im\big(f(a + ih)\big)/h\f$
approximates \f$f'(a)\f$ with no subtraction of nearby values. The cancellation disappears, \f$h\f$
may be taken as small as the representation allows, and the first derivative is obtained to full
precision.

It gives the first derivative only. The second appears in the real part,
\f$\Re\big(f(a + ih)\big) = f(a) - \frac{h^2}{2}f''(a) + O(h^4)\f$, and recovering it subtracts
\f$f(a)\f$ and reintroduces the cancellation.

The method also requires:

  + a real analytic function;
  + an implementation that accepts complex arguments and stays analytic through every branch it
    takes.

# Comparison of methods {#flx_summary}

| Method | Accuracy | Orders | What it needs |
|--------|-----------|:------:|---------------|
| Symbolic | rounding only | any, with expression growth | a formula |
| Forward mode | rounding only | any; \f$2^n\f$ components with hyperduals | the program and a type it accepts |
| Reverse mode | rounding only | first, higher by nesting | the program and a record of its execution |
| Difference quotient | half the digits, at best | any, degrading fast | nothing |
| Complex step | rounding only | first only | a real analytic function and complex arithmetic |

| Method | In the library |
|--------|----------------|
| Symbolic differentiation | Planned as a second layer: an expression carrying its own derivative as another expression, differentiated once and evaluated any number of times. |
| Forward mode | Yes, and it is the whole of the library: hyperduals up to order 4, on scalars and on SIMD registers alike. |
| Reverse mode | No. It serves many inputs and few outputs, and requires a separate design. |
| Complex step | No. The nilpotent units remove the step at every order; the complex step removes it at the first only. |
| Difference quotient | No. It approximates what an arithmetic method computes exactly. |

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
