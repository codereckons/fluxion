The EVE Fluxion module
======================

**FLUXION** is an implementation based on the **EVE** providing implementation for
scalar and SIMD versions of mathematical functions derivative and differential.
It's a C++20 and onward implementation of a type based wrapper around SIMD extensions sets for most current architectures.
It aims at showing how C++20 can be used to design and implement efficient, low level, high abstraction library suited for high performances.

It's a research project first and an open source library second. We reserve the right to change API and baseline
compiler required until the first official 0.1 release. However, we'll try to minimize disruption. Semantic versioning
will ensure API retro-compatibility if anything huge needs to change.

What is fluxion about?
======================

    'fluxion' is the name used by Isaac newton to denote what is now more often called derivatives
    in modern mathematic terminology.

    This module brings (up to now) to main parts:

     - the avaibility to compute the first order derivatives or differentials of most EVE mathematical functions
     - a forward automatic implementation of derivatives computation allowing to compute derivatives of
       of any almost any derivable fonction as soon as it has been written generically using EVE function calls

    It must be noted that this is available for floating point or eve::complex with scalar or simd valus.

Derivatives of EVE functions
============================

 This implementation allows to compute values of first order partial derivatives of EVE functions by decorating them.

 fluxion derivatives use a small set of decorators, namely:

   - derivative (or derivative_1st)
   - derivative_2nd
   - derivative_3rd
   - derivative_nth<N>

  To be clear, for an EVE function \f$f\f$ of four variables \f$f(x, y, z, t)\f$

     -  'derivative(f)(x, y, z, t)' or 'derivative_1st(f)(x, y, z, t)' will computes \f$\frac{\partial{f}}{\partial{x}}\f$
     -  'derivative_2nd(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{y}}\f$
     -  'derivative_3rd(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{z}}\f$
     -  'derivative_nth<4>(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{t}}\f$
     -  'derivative_nth<N>(f)(x, y, z, t)' returns 0 as soon as N exceeds the number of parameters of \f$f\f$.

 @note  If a function parameter type cannot be floating point based, the result of the derivative relative
        to this parameter is 0.

 @warning Let us insist on the fact that 1st,  2nd, 3rd or nth<N> DO NOT refer to the order of derivation but to the
          index (starting from 1) of the derivation variable used in the fonction call.


 Here is the list of EVE function that supports the decorators. Of course all EVE floating point or complex constants
 can be added to the list. Their derivatives are always 0.


 @warning Be aware that for complex arguments the derivation is only possible if the function is analytic.
          In particular all functions below involving modulus (absolute value) are not derivable in the complex
          domain.

 @warning Some of these functions are not derivable everywhere (the obvious case being eve::abs at 0)
          If the function is not derivable at some point the value of its derivative is implementation
          dependent and can be considered as defined, but meaningless (up to now).

# core functions

|     abs          |  dist  |  fsm       |  minus     |  rec      |
|     absmax       |  div   |  fsnm      |  mul       |  rem      |
|     absmin       |  fam   |  inc       |  nearest   |  round    |
|     add          |  fanm  |  lerp      |  negabsmax |  rsqrt    |
|     average      |  fdim  |  manhattan |  negabsmin |  sign     |
|     binarize     |  floor |  maxabs    |  negate    |  signnz   |
|     binarize_not |  fma   |  max       |  negatenz  |  sqr_abs  |
|     ceil         |  fms   |  maxmag    |  negmaxabs |  sqr      |
|     clamp        |  fnma  |  minabs    |  negminabs |  sqrt     |
|     copysign     |  fnms  |  min       |  oneminus  |  sub      |
|     dec          |  frac  |  minmag    |  plus      |  trunc    |

# math functions

|     acosd   | asind    | cot       | log2          | sincos     |
|     acosh   | asinh    | cotpi     | log_abs       | sindcosd   |
|     acos    | asin     | cscd      | log           | sind           |
|     acospi  | asinpi   | csch      | logspace_add  | sinhc      |
|     acotd   | atan2d   | csc       | logspace_sub  | sinhcosh   |
|     acoth   | atan2    | cscpi     | lpnorm        | sinh           |
|     acot    | atan2pi  | deginrad  | nthroot       | sin            |
|     acotpi  | atand    | exp10     | pow1p         | sinpic     |
|     acscd   | atanh    | exp2      | pow_abs       | sinpicospi |
|     acsch   | atan     | exp       | pow           | sinpi      |
|     acsc    | atanpi   | expm1     | powm1         | tand           |
|     acscpi  | cbrt     | expmx2    | radindeg      | tanh           |
|     agd     | cosd     | expx2     | radinpi       | tan            |
|     arg     | cosh     | gd        | secd          | tanpi      |
|     asecd   | cos      | geommean  | sech          |                |
|     asech   | cospi    | hypot     | sec           |                |
|     asec    | cotd     | log10     | secpi         |                |
|     asecpi  | coth     | log1p     | sinc          |                |

# special functions

|     beta        |  erfc_inv  | gamma_p    | lrising_factorial |
|     betainc     |  erfcx     | lambert    | omega             |
|     betainc_inv |  erf       | lbeta      | rising_factorial  |
|     dawson      |  erf_inv   | lgamma     | signgam           |
|     erfc        |  exp_int   | log_gamma  | tgamma            |

 @caveat for obvious reasons some of the special functions cannot be derived according all parameters
         return 0 when derived according this parameter.

polynomial functions
|     gegenbauer  | horner  | laguerre  | reverse_horner |
|     hermite     | jacobi  | legendre  | tchebytchev    |

 Bessel functions

|       airy_ai        | cyl_bessel_j0 |  cyl_bessel_kn |  sph_bessel_j1 |
|       airy_bi        | cyl_bessel_j1 |  cyl_bessel_y0 |  sph_bessel_jn |
|       cyl_bessel_i0  | cyl_bessel_jn |  cyl_bessel_y1 |  sph_bessel_y0 |
|       cyl_bessel_i1  | cyl_bessel_k0 |  cyl_bessel_yn |  sph_bessel_y1 |
|       cyl_bessel_in  | cyl_bessel_k1 |  sph_bessel_j0 |  sph_bessel_yn |

 @caveat up to now bessel functions accept only real parameters and bessel function whose first parameter is the order
         return 0 when derived according this parameter.

# Automatic forward derivation

 Computing derivative is not restricted to **EVE** functions.
 Fluxion allows to compute values of differential of almost any EVE based function using specialized parameters.

 eve::valder<T> is a product type with two fields: the value and the derivative value.

 for example if 'x' is a floating point value of type double: 'double x = 3.0'.

  'auto vx = eve::var(x)' is a  'valder<T>' element for which

   - 'val(vx)' is 'x'
   - 'der(vx)' is 'one(as(x))'

  simply denoting the fact that the derivative of the identity is 1.

 now if f =  [}(auto x){eve::sqr(x)*3+2*x); }

 the call auto y = f(valder(3.0)) will return a 'valder<double>' element for which

   - 'val(y)' is 33.0;
   - 'der(y)' is 20.0,  that is the value of the derivative of f at 3.0 (the value of 6.0*x+2.0);

 In this scheme all variables that are not of valder like types are considered as constants (i.e. of zero derivative)

 See the Newton-Raphson tutorial to look further in expanations.

#  Other functions or functionnals

   - gradient For a function f of n variables x1, ... gradien(result, f, x1, ...) set in the range result the n values
     of the partial derivatives of f at x1, ...
   - differential a function f of n variables x1, ...,  the differential of f at   x1, ... is a function that invoked
     at dx1, ... returms the scalar product of the gradient by the vector of dxi.
