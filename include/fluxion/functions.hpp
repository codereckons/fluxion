//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/decorators.hpp>

// #include <eve/module/core.hpp>
// #include <eve/module/math.hpp>
// #include <eve/module/special.hpp>
// #include <eve/module/bessel.hpp>

//======================================================================================================================
//! @defgroup functions Hyperdual Functions
//! @brief Functions performing computations over all hyperdual types
//======================================================================================================================

//======================================================================================================================
// Fundamental functions
//======================================================================================================================
#include <fluxion/functions/parts.hpp>
#include <fluxion/functions/d.hpp>
#include <fluxion/functions/abs.hpp>
#include <fluxion/functions/convert.hpp>
#include <fluxion/functions/pure.hpp>
#include <fluxion/functions/if_else.hpp>

//======================================================================================================================
// Arithmetic and math
//======================================================================================================================
#include <fluxion/functions/acos.hpp>
#include <fluxion/functions/acosh.hpp>
#include <fluxion/functions/acospi.hpp>
#include <fluxion/functions/acot.hpp>
#include <fluxion/functions/acoth.hpp>
#include <fluxion/functions/acotpi.hpp>
#include <fluxion/functions/acsc.hpp>
#include <fluxion/functions/acscpi.hpp>
#include <fluxion/functions/acsch.hpp>
#include <fluxion/functions/add.hpp>
#include <fluxion/functions/agd.hpp>
//#include <fluxion/functions/am.hpp> g++ pb ?
#include <fluxion/functions/asec.hpp>
#include <fluxion/functions/asecpi.hpp>
#include <fluxion/functions/asech.hpp>
#include <fluxion/functions/asin.hpp>
#include <fluxion/functions/asinpi.hpp>
#include <fluxion/functions/asinh.hpp>
#include <fluxion/functions/atan.hpp>
#include <fluxion/functions/atan2.hpp>
#include <fluxion/functions/atanh.hpp>
#include <fluxion/functions/atanpi.hpp>
#include <fluxion/functions/atanpi.hpp>
#include <fluxion/functions/average.hpp>

// #include <fluxion/functions/beta.hpp>  //needs tgamma
#include <fluxion/functions/ceil.hpp>
#include <fluxion/functions/chi.hpp>
#include <fluxion/functions/cos.hpp>
#include <fluxion/functions/cosh.hpp>
#include <fluxion/functions/cospi.hpp>
#include <fluxion/functions/cot.hpp>
#include <fluxion/functions/cotpi.hpp>
#include <fluxion/functions/coth.hpp>
#include <fluxion/functions/csc.hpp>
#include <fluxion/functions/cscpi.hpp>
#include <fluxion/functions/csch.hpp>
#include <fluxion/functions/dec.hpp>
// #include <fluxion/functions/deta.hpp>    // complex needed
// #include <fluxion/functions/digamma.hpp> // needs polygamma
#include <fluxion/functions/dist.hpp>
#include <fluxion/functions/div.hpp>
#include <fluxion/functions/dot.hpp>
// #include <fluxion/functions/ellint_fe.hpp>
// #include <fluxion/functions/ellint_rc.hpp>
// #include <fluxion/functions/ellint_rd.hpp>
// #include <fluxion/functions/ellint_rf.hpp>
// #include <fluxion/functions/ellint_rg.hpp>
// #include <fluxion/functions/ellint_rj.hpp>
// #include <fluxion/functions/erf.hpp>
// #include <fluxion/functions/erfcx.hpp>
// #include <fluxion/functions/erfi.hpp>
// #include <fluxion/functions/eta.hpp>
#include <fluxion/functions/exp.hpp>
// #include <fluxion/functions/exp10.hpp>
// #include <fluxion/functions/exp2.hpp>
// #include <fluxion/functions/exp_i.hpp>
// #include <fluxion/functions/exp_ipi.hpp>
// #include <fluxion/functions/expm1.hpp>
// #include <fluxion/functions/expmx2.hpp>
// #include <fluxion/functions/expx2.hpp>
// #include <fluxion/functions/faddeeva.hpp>
// #include <fluxion/functions/fam.hpp>
// #include <fluxion/functions/floor.hpp>
#include <fluxion/functions/fma.hpp>
// #include <fluxion/functions/fms.hpp>
// #include <fluxion/functions/fnma.hpp>
// #include <fluxion/functions/fnms.hpp>
// #include <fluxion/functions/frac.hpp>
// #include <fluxion/functions/from_polar.hpp>
// #include <fluxion/functions/fsm.hpp>
// #include <fluxion/functions/gd.hpp>
// #include <fluxion/functions/gegenbauer.hpp>
// #include <fluxion/functions/hypergeometric.hpp>
// #include <fluxion/functions/hypot.hpp>
// #include <fluxion/functions/horner.hpp>
#include <fluxion/functions/inc.hpp>
// #include <fluxion/functions/is_cinf.hpp>
// #include <fluxion/functions/is_denormal.hpp>
#include <fluxion/functions/is_equal.hpp>
#include <fluxion/functions/is_eqz.hpp>
// #include <fluxion/functions/is_finite.hpp>
// #include <fluxion/functions/is_flint.hpp>
// #include <fluxion/functions/is_fnan.hpp>
#include <fluxion/functions/is_infinite.hpp>
// #include <fluxion/functions/is_imag.hpp>
// #include <fluxion/functions/is_nan.hpp>
// #include <fluxion/functions/is_nez.hpp>
// #include <fluxion/functions/is_not_cinf.hpp>
// #include <fluxion/functions/is_not_denormal.hpp>
#include <fluxion/functions/is_not_equal.hpp>
// #include <fluxion/functions/is_not_finite.hpp>
// #include <fluxion/functions/is_not_flint.hpp>
// #include <fluxion/functions/is_not_fnan.hpp>
// #include <fluxion/functions/is_not_infinite.hpp>
// #include <fluxion/functions/is_not_nan.hpp>
// #include <fluxion/functions/is_not_real.hpp>
// #include <fluxion/functions/is_pure.hpp>
// #include <fluxion/functions/is_real.hpp>
// #include <fluxion/functions/is_unitary.hpp>
// #include <fluxion/functions/jacobi_elliptic.hpp>
// #include <fluxion/functions/kummer.hpp>
// #include <fluxion/functions/lambda.hpp>
// #include <fluxion/functions/lbeta.hpp>
// #include <fluxion/functions/ldiv.hpp>
// #include <fluxion/functions/legendre.hpp>
// #include <fluxion/functions/lerp.hpp>
#include <fluxion/functions/log.hpp>
// #include <fluxion/functions/log10.hpp>
// #include <fluxion/functions/log1p.hpp>
// #include <fluxion/functions/log_abs.hpp>
// #include <fluxion/functions/log_abs_gamma.hpp>
// #include <fluxion/functions/log_gamma.hpp>
// #include <fluxion/functions/log2.hpp>
// #include <fluxion/functions/lpnorm.hpp>
// #include <fluxion/functions/lrising_factorial.hpp>
// #include <fluxion/functions/rising_factorial.hpp>
// #include <fluxion/functions/manhattan.hpp>
// #include <fluxion/functions/maxabs.hpp>
// #include <fluxion/functions/maxmag.hpp>
// #include <fluxion/functions/minabs.hpp>
// #include <fluxion/functions/minmag.hpp>
// #include <fluxion/functions/minus.hpp>
#include <fluxion/functions/mul.hpp>
// #include <fluxion/functions/muli.hpp>
// #include <fluxion/functions/mulmi.hpp>
// #include <fluxion/functions/nearest.hpp>
// #include <fluxion/functions/negmaxabs.hpp>
// #include <fluxion/functions/negminabs.hpp>
#include <fluxion/functions/oneminus.hpp>
// #include <fluxion/functions/pow.hpp>
// #include <fluxion/functions/pow1p.hpp>
// #include <fluxion/functions/pow_abs.hpp>
// #include <fluxion/functions/powm1.hpp>
// #include <fluxion/functions/proj.hpp>
// #include <fluxion/functions/radinpi.hpp>
#include <fluxion/functions/rec.hpp>
// #include <fluxion/functions/reldist.hpp>
// #include <fluxion/functions/reverse_horner.hpp>
#include <fluxion/functions/rsqrt.hpp>
// #include <fluxion/functions/sec.hpp>
// #include <fluxion/functions/secpi.hpp>
// #include <fluxion/functions/sech.hpp>
// #include <fluxion/functions/sign.hpp>
#include <fluxion/functions/sin.hpp>
// #include <fluxion/functions/sinc.hpp>
// #include <fluxion/functions/sincos.hpp>
// #include <fluxion/functions/sinpi.hpp>
// #include <fluxion/functions/sinpicospi.hpp>
#include <fluxion/functions/sinh.hpp>
// #include <fluxion/functions/sinhc.hpp>
// #include <fluxion/functions/sinhcosh.hpp>
// #include <fluxion/functions/slerp.hpp>
// #include <fluxion/functions/sqr.hpp>
// #include <fluxion/functions/sqr_abs.hpp>
#include <fluxion/functions/sqrt.hpp>
// #include <fluxion/functions/sub.hpp>
#include <fluxion/functions/tan.hpp>
// #include <fluxion/functions/tanpi.hpp>
// #include <fluxion/functions/tanh.hpp>
// #include <fluxion/functions/tchebytchev.hpp>
// #include <fluxion/functions/tgamma.hpp>           //needs polygamma
// #include <fluxion/functions/tgamma_inv.hpp>
// #include <fluxion/functions/to_cylindrical.hpp>
#include <fluxion/functions/to_dual.hpp>
#include <fluxion/functions/to_dual2.hpp>
#include <fluxion/functions/to_dual3.hpp>
#include <fluxion/functions/to_dual4.hpp>
// #include <fluxion/functions/to_polar.hpp>
// #include <fluxion/functions/tricomi.hpp>
// #include <fluxion/functions/trunc.hpp>
// #include <fluxion/functions/zeta.hpp>

// #include <fluxion/functions/bessel_j.hpp>
// #include <fluxion/functions/bessel_y.hpp>
// #include <fluxion/functions/bessel_h.hpp>
// #include <fluxion/functions/bessel_i.hpp>
// #include <fluxion/functions/bessel_k.hpp>

// #include <fluxion/functions/airy.hpp>
// #include <fluxion/functions/airy_ai.hpp>
// #include <fluxion/functions/airy_bi.hpp>

// //======================================================================================================================
// // Functions performing computations over quaternion complex or real elements only.
// //======================================================================================================================

// #include <fluxion/functions/align.hpp>
// #include <fluxion/functions/from_angle_axis.hpp>
// #include <fluxion/functions/from_cylindrical.hpp>
// #include <fluxion/functions/from_cylindrospherical.hpp>
// #include <fluxion/functions/from_euler.hpp>
// #include <fluxion/functions/from_multipolar.hpp>
// #include <fluxion/functions/from_rotation_matrix.hpp>
// #include <fluxion/functions/from_semipolar.hpp>
// #include <fluxion/functions/from_spherical.hpp>
// #include <fluxion/functions/rot_angle.hpp>
// #include <fluxion/functions/rot_axis.hpp>
// #include <fluxion/functions/rotate_vec.hpp>
// #include <fluxion/functions/to_angle_axis.hpp>
// #include <fluxion/functions/to_cylindrical.hpp>
// #include <fluxion/functions/to_cylindrospherical.hpp>
// #include <fluxion/functions/to_euler.hpp>
// #include <fluxion/functions/to_multipolar.hpp>
// #include <fluxion/functions/to_rotation_matrix.hpp>
// #include <fluxion/functions/to_semipolar.hpp>
// #include <fluxion/functions/to_spherical.hpp>
