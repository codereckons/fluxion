//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup fluxion functions
//! @brief first order derivation of Mathematical functions
//!
//! This module provides implementation for
//! scalar and SIMD versions of mathematical functions derivative and differential.
//!
//! **Required header:** @code{.cpp} #include <flx/flx.hpp> @endcode
//!
//! @}
//==================================================================================================

//==================================================================================================
//! @addtogroup fluxion
//! @{
//!    'fluxion' is the name used by Isaac newton to denote what is now more often called derivatives
//!    in modern mathematic terminology.
//!
//!    This module brings (up to now) to main parts:
//!
//!     - the avaibility to compute the first order derivatives or differentials of most EVE mathematical functions
//!     - a forward automatic implementation of derivatives computation allowing to compute derivatives of
//!       of any almost any derivable fonction as soon as it has been written generically using EVE function calls
//!
//!    It must be noted that this is available for floating point or eve::complex scalar or simd valus.
//!
//!
//! @defgroup derivatives
//! @ingroup fluxion
//!
//! These functions allow to compute values of first order partial derivatives of EVE functions by decorating them.
//!
//! fluxion derivatives uses a small set of decorators, namely:
//!
//!   - derivative (or derivative_1st)
//!   - derivative_2nd
//!   - derivative_3rd
//!   - derivative_nth<N>
//!
//!  To be clear, for an EVE function \f$f\f$ of four variables \f$f(x, y, z, t)\f$
//!
//!     -  'derivative(f)(x, y, z, t)' or 'derivative_1st(f)(x, y, z, t)' will computes \f$\frac{\partial{f}}{\partial{x}}\f$
//!     -  'derivative_2nd(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{y}}\f$
//!     -  'derivative_3rd(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{z}}\f$
//!     -  'derivative_nth<4>(f)(x, y, z, t)' computes \f$\frac{\partial{f}}{\partial{t}}\f$
//!     -  'derivative_nth<N>(f)(x, y, z, t)' returns 0 as soon as N exceeds the number of parameters of \f$f\f$.
//!
//! @note  If a function parameter is not floating point based the result of the derivative relative to this parameter is 0.
//!
//! @warning Let us insist on the fact that 1st,  2nd, 3rd or nth<N> DO NOT refer to the order of derivation but to the
//!          index (starting from 1) of the derivation variable used in the fonction call.
//!
//!
//! Here is the list of EVE function that supports the decorators. Of course all EVE floating point or complex constants
//! can be put in the list. Their derivatives are always 0.
//!
//!
//! @warning Be aware that for complex arguments the derivation is only possible if the function is analytic.
//!          In particular all functions below involving modulus (abslute value) are not derivable in the complex
//!          domain.
//!
//! @warning Some of these functions are not derivable everywhere (the obvious cas being eve::abs at 0)
//!          If the function is not derivable at some point the value of its derivative is implementation
//!          dependent and can be considered as defined, but meaningless.
//!
//! core functions
//!     abs.hpp           dist.hpp   fsm.hpp        minus.hpp      rec.hpp
//!     absmax.hpp        div.hpp    fsnm.hpp       mul.hpp        rem.hpp
//!     absmin.hpp        fam.hpp    inc.hpp        nearest.hpp    round.hpp
//!     add.hpp           fanm.hpp   lerp.hpp       negabsmax.hpp  rsqrt.hpp
//!     average.hpp       fdim.hpp   manhattan.hpp  negabsmin.hpp  sign.hpp
//!     binarize.hpp      floor.hpp  maxabs.hpp     negate.hpp     signnz.hpp
//!     binarize_not.hpp  fma.hpp    max.hpp        negatenz.hpp   sqr_abs.hpp
//!     ceil.hpp          fms.hpp    maxmag.hpp     negmaxabs.hpp  sqr.hpp
//!     clamp.hpp         fnma.hpp   minabs.hpp     negminabs.hpp  sqrt.hpp
//!     copysign.hpp      fnms.hpp   min.hpp        oneminus.hpp   sub.hpp
//!     dec.hpp           frac.hpp   minmag.hpp     plus.hpp       trunc.hpp

//! math functions
//!     acosd.hpp   asind.hpp    cot.hpp       log2.hpp          sincos.hpp
//!     acosh.hpp   asinh.hpp    cotpi.hpp     log_abs.hpp       sindcosd.hpp
//!     acos.hpp    asin.hpp     cscd.hpp      log.hpp           sind.hpp
//!     acospi.hpp  asinpi.hpp   csch.hpp      logspace_add.hpp  sinhc.hpp
//!     acotd.hpp   atan2d.hpp   csc.hpp       logspace_sub.hpp  sinhcosh.hpp
//!     acoth.hpp   atan2.hpp    cscpi.hpp     lpnorm.hpp        sinh.hpp
//!     acot.hpp    atan2pi.hpp  deginrad.hpp  nthroot.hpp       sin.hpp
//!     acotpi.hpp  atand.hpp    exp10.hpp     pow1p.hpp         sinpic.hpp
//!     acscd.hpp   atanh.hpp    exp2.hpp      pow_abs.hpp       sinpicospi.hpp
//!     acsch.hpp   atan.hpp     exp.hpp       pow.hpp           sinpi.hpp
//!     acsc.hpp    atanpi.hpp   expm1.hpp     powm1.hpp         tand.hpp
//!     acscpi.hpp  cbrt.hpp     expmx2.hpp    radindeg.hpp      tanh.hpp
//!     agd.hpp     cosd.hpp     expx2.hpp     radinpi.hpp       tan.hpp
//!     arg.hpp     cosh.hpp     gd.hpp        secd.hpp          tanpi.hpp
//!     asecd.hpp   cos.hpp      geommean.hpp  sech.hpp
//!     asech.hpp   cospi.hpp    hypot.hpp     sec.hpp
//!     asec.hpp    cotd.hpp     log10.hpp     secpi.hpp
//!     asecpi.hpp  coth.hpp     log1p.hpp     sinc.hpp

//!special functions
//!     beta.hpp         erfc_inv.hpp  gamma_p.hpp    lrising_factorial.hpp
//!     betainc.hpp      erfcx.hpp     lambert.hpp    omega.hpp
//!     betainc_inv.hpp  erf.hpp       lbeta.hpp      rising_factorial.hpp
//!     dawson.hpp       erf_inv.hpp   lgamma.hpp     signgam.hpp
//!     erfc.hpp         exp_int.hpp   log_gamma.hpp  tgamma.hpp
//!
//! @caveat for obvious reasons some of the special functions cannot be derived according all parameters
//!         return 0 when derived according this parameter.

//!polynomial functions
//!    gegenbauer.hpp  horner.hpp  laguerre.hpp  reverse_horner.hpp
//!    hermite.hpp     jacobi.hpp  legendre.hpp  tchebytchev.hpp

//! Bessel functions
//!
//!      airy_ai.hpp        cyl_bessel_j0.hpp  cyl_bessel_kn.hpp  sph_bessel_j1.hpp
//!      airy_bi.hpp        cyl_bessel_j1.hpp  cyl_bessel_y0.hpp  sph_bessel_jn.hpp
//!      cyl_bessel_i0.hpp  cyl_bessel_jn.hpp  cyl_bessel_y1.hpp  sph_bessel_y0.hpp
//!      cyl_bessel_i1.hpp  cyl_bessel_k0.hpp  cyl_bessel_yn.hpp  sph_bessel_y1.hpp
//!      cyl_bessel_in.hpp  cyl_bessel_k1.hpp  sph_bessel_j0.hpp  sph_bessel_yn.hpp
//!
//! @caveat up to now bessel functions accept only real parameters and bessel function whose first parameter is the order
//!         return 0 when derived according this parameter.

//! @defgroup forward_automaic
//! @ingroup fluxion
//!
//! These module allow to compute values of differential of almost any EVE based function using spcialized parameters.
//!
//! eve::valder<T> is a product type with two fields the value and the derivative value
//!
//! for example if x is a floating point value of type double double x = 3.0.
//!
//!  auto vx = eve::var(x) is a  valder<T> element for which
//!
//!   - val(vx) is x
//!   - der(vx) is one(as(x))
//!
//!  simply denoting the fact that the derivative of the identity is 1.
//!
//! now if f =  [}(auto x){eve::sqr(x)*3+2*x); }
//!
//! the call auto y f(valder(3.0)) wille return a valder<double> for which
//!
//!   - val(y) is 33.0;
//!   - der(y) is 20.0,  that is the value of the derivative of f at 3.0 (the value of 6.0*x+2.0);
//!
//! In this scheme all variables that are not of valder like types are considered as constants (i.e. of zero derivative)
//!
//! Other functions
//!
//!   - gradient For a function f of n variables x1, ... gradien(result, f, x1, ...) set in the range result the n values
//!     of the partial derivatives of f at x1, ...
//!   - differential a function f of n variables x1, ...,  the differential of f at   x1, ... is a function that invoked
//!     at dx1, ... returms the scalar product of the gradient by the vector of dxi.
//!
///! @}
//==================================================================================================


//==================================================================================================
//! @namespace flx
//! @brief Main fluxion namespace
//==================================================================================================
namespace flx
{

}

#include <flx/analytic/analytic.hpp>
#include <flx/derivative/derivatives.hpp>
#include <flx/forward_automatic/forward_automatic.hpp>
