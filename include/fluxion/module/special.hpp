//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/decorators.hpp>

#include <fluxion/module/core.hpp>
#include <fluxion/module/math.hpp>

#include <eve/module/special.hpp>
// #include <eve/module/bessel.hpp>

//======================================================================================================================
//! @defgroup functions Hyperdual Functions
//! @brief Functions performing computations over all hyperdual types
//!   relative to "special" functions
//======================================================================================================================
#include <fluxion/module/special/am.hpp>
// #include <fluxion/module/special/beta.hpp>  //needs tgamma
// #include <fluxion/module/special/digamma.hpp> // needs polygamma
// #include <fluxion/module/special/ellint_e.hpp> // can be done
// #include <fluxion/module/special/ellint_fe.hpp>
// #include <fluxion/module/special/ellint_rc.hpp>
// #include <fluxion/module/special/ellint_rd.hpp>
// #include <fluxion/module/special/ellint_rf.hpp>
// #include <fluxion/module/special/ellint_rg.hpp>
// #include <fluxion/module/special/ellint_rj.hpp>
#include <fluxion/module/special/erf.hpp>
#include <fluxion/module/special/erfc.hpp>
#include <fluxion/module/special/erfcx.hpp>
// #include <fluxion/module/special/hypergeometric.hpp> // complex neededhttps:
                       //functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F1/20/01/04/
// #include <fluxion/module/special/jacobi_elliptic.hpp> //to see
// #include <fluxion/module/special/lbeta.hpp> //needs polygamma
#include <fluxion/module/special/log_abs_gamma.hpp> //needs polygamma
#include <fluxion/module/special/log_gamma.hpp>> //needs polygamma
// #include <fluxion/module/special/lrising_factorial.hpp> //needs polygamma
// #include <fluxion/module/special/rising_factorial.hpp> //needs polygamma
#include <fluxion/module/special/tgamma.hpp>           //first derivative only
// #include <fluxion/module/special/tgamma_inv.hpp>  //needs polygamma
// #include <fluxion/module/special/bessel_j.hpp>
// #include <fluxion/module/special/bessel_y.hpp>
// #include <fluxion/module/special/bessel_h.hpp>
// #include <fluxion/module/special/bessel_i.hpp>
// #include <fluxion/module/special/bessel_k.hpp>

// #include <fluxion/module/special/airy.hpp>
// #include <fluxion/module/special/airy_ai.hpp>
// #include <fluxion/module/special/airy_bi.hpp>
