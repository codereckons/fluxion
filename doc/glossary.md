Glossary  {#flx_glossary}
==========================

The terms these pages use.

# Floating-point arithmetic {#flx_gl_float}

## Unit roundoff

The largest relative error a single correctly rounded floating-point operation can make, written
\f$u\f$. It is \f$2^{-24}\f$ for `float` and \f$2^{-53}\f$ for `double`, and it sets the number of
digits any result can hold.

## Cancellation

The loss of significant digits when two nearby values are subtracted. The difference is computed
exactly, and the digits the two operands had in common are gone from it, so the error they already
carried becomes the leading part of the result. It is what a difference quotient runs into as
\f$h\f$ shrinks.

## Truncation error

The part of a formula that is dropped. A forward difference omits a term of order \f$h\f$, which is
its truncation error, and it shrinks with \f$h\f$ where the cancellation grows.

# Algebra {#flx_gl_algebra}

## Nilpotent

An element whose power vanishes. The units of @ref flx_algebra satisfy \f$\varepsilon_i^2 = 0\f$,
and any element with no real part satisfies \f$N^{n+1} = 0\f$ at order \f$n\f$.

## Order

In **FLUXION**, the number of nilpotent units a value carries, written `Ord` in the types. A value
of order \f$n\f$ holds \f$2^n\f$ components and answers derivatives up to the \f$n\f$-th.

# Vector registers {#flx_gl_simd}

## Cardinal

The number of lanes of a SIMD register, EVE's term, read by `eve::cardinal_v`. It counts the points
evaluated together, where the order counts the derivatives one point carries.

## Structure of arrays

A layout storing one array per field rather than one record per element. `eve::wide` of a hyperdual
holds one register per component, so an operation on a component is one SIMD instruction.

# Automatic differentiation {#flx_gl_ad}

## Seeding

Giving a value the nilpotent units the derivatives against it will be indexed by. Griewank and
Walther's term for the same operation in the forward mode.

## Forward mode

Automatic differentiation carrying the derivatives alongside the value, in the order the program
computes. One pass returns the value and the derivatives with respect to whatever was seeded.

## Reverse mode

Automatic differentiation recording the operations of an evaluation, then walking the record
backwards to accumulate derivatives. One forward pass and one backward pass return the gradient
against every input, at the cost of storing the record.

<div class="section_buttons">

| Previous                        |
|:--------------------------------|
| [Background](@ref background)   |

</div>
