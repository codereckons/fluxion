Glossary  {#flx_glossary}
==========================

# Floating-point arithmetic {#flx_gl_float}

## Unit roundoff

The largest relative error a single correctly rounded floating-point operation can make, written
\f$u\f$. It is \f$2^{-24}\f$ for `float` and \f$2^{-53}\f$ for `double`, and it sets the number of
digits any result can hold.

## Cancellation

The loss of significant digits when two nearby values are subtracted. The difference is computed
exactly, and the digits the two operands had in common disappear from it, so the error they already
carried becomes the leading part of the result. It limits a difference quotient as \f$h\f$ shrinks.

## Truncation error

The part of a formula that is dropped. A forward difference omits a term of order \f$h\f$, which is
its truncation error, and it shrinks with \f$h\f$ while the cancellation grows.

# Algebra {#flx_gl_algebra}

## Unit

A symbol \f$\varepsilon_i\f$ adjoined to the reals with \f$\varepsilon_i \neq 0\f$ and
\f$\varepsilon_i^2 = 0\f$, called the dual unit in the literature, defined in @ref flx_one_unit. An
element of order \f$n\f$ carries \f$n\f$ of them, and each of its components is indexed by the set
of units that component carries. The unit roundoff of @ref flx_gl_float is an unrelated term.

## Nilpotent

An element some power of which is zero. The units of @ref flx_algebra satisfy
\f$\varepsilon_i^2 = 0\f$, and any element with no real part satisfies \f$N^{n+1} = 0\f$ at order
\f$n\f$.

## Order

In **FLUXION**, the number of nilpotent units an element carries, written `Ord` in the types. An
element of order \f$n\f$ holds \f$2^n\f$ components and derivatives up to the \f$n\f$-th.

# SIMD registers {#flx_gl_simd}

## Cardinal

EVE's term for the number of lanes of a SIMD register, read by `eve::cardinal_v`. It counts the
points evaluated together, while the order counts the derivatives one point carries.

## Structure of arrays

A layout storing one array per field rather than one record per element. `eve::wide` of a hyperdual
holds one register per component, so an operation on a component is one SIMD instruction.

# Automatic differentiation {#flx_gl_ad}

## Seeding

Assigning nilpotent units to an argument, so that the derivatives with respect to it are indexed by
those units. Griewank and Walther's term for the same operation in forward mode. In **FLUXION** it
is `flx::variable`, `flx::variables`, and the `flx::var` constructor (see @ref flx_assignment).

## Forward mode

Automatic differentiation carrying the derivatives alongside the value, in the sequence the program
computes. One pass returns the value and the derivatives with respect to the seeded arguments.

## Reverse mode

Automatic differentiation recording the operations of an evaluation, then traversing the record
backward to accumulate derivatives. One forward pass, which stores the record, and one backward pass
return the gradient with respect to every input.

<div class="section_buttons">

| Previous                        |
|:--------------------------------|
| [Background](@ref background)   |

</div>
