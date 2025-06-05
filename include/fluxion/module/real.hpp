//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/decorators.hpp>

//======================================================================================================================
//! @defgroup functions Hyperdual Functions
//! @brief Functions performing computations over all hyperdual types with floating point real base
//!        i.e. real,  not complex derivatives.
//======================================================================================================================

#include<fluxion/module/math.hpp>
#include<fluxion/module/special.hpp>
//======================================================================================================================
// Fundamental functions
//======================================================================================================================
#include <fluxion/module/real/abs.hpp>
#include <fluxion/module/real/absmax.hpp>
#include <fluxion/module/real/absmin.hpp>
#include <fluxion/module/real/ceil.hpp>
#include <fluxion/module/real/chi.hpp>
#include <fluxion/module/real/copysign.hpp>
#include <fluxion/module/real/dist.hpp>
#include <fluxion/module/real/floor.hpp>
#include <fluxion/module/real/frac.hpp>
#include <fluxion/module/real/hypot.hpp>

#include <fluxion/module/real/is_greater.hpp>
#include <fluxion/module/real/is_greater_equal.hpp>
#include <fluxion/module/real/is_less.hpp>
#include <fluxion/module/real/is_less_equal.hpp>
#include <fluxion/module/real/is_not_greater.hpp>
#include <fluxion/module/real/is_not_greater_equal.hpp>
#include <fluxion/module/real/is_not_less.hpp>
#include <fluxion/module/real/is_not_less_equal.hpp>

#include <fluxion/module/real/log_abs.hpp>
// #include <fluxion/module/real/log_abs_gamma.hpp> //needs polygamma
#include <fluxion/module/real/lpnorm.hpp>
#include <fluxion/module/real/manhattan.hpp>
#include <fluxion/module/real/maxabs.hpp>
#include <fluxion/module/real/minabs.hpp>
#include <fluxion/module/real/nearest.hpp>
#include <fluxion/module/real/negmaxabs.hpp>
#include <fluxion/module/real/negminabs.hpp>
#include <fluxion/module/real/pow_abs.hpp>
#include <fluxion/module/real/reldist.hpp>
#include <fluxion/module/real/sign.hpp>
#include <fluxion/module/real/signnz.hpp>
#include <fluxion/module/real/sqr_abs.hpp>
#include <fluxion/module/real/trunc.hpp>
