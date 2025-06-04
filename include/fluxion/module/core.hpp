//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/decorators.hpp>

#include <eve/module/core.hpp>

// #include <eve/module/special.hpp>
// #include <eve/module/bessel.hpp>

//======================================================================================================================
//! @defgroup functions Hyperdual Functions
//! @brief Functions performing computations over all hyperdual types
//! with predicates or arithmetic flavours
//======================================================================================================================

//======================================================================================================================
// Fundamental functions
//======================================================================================================================
#include <fluxion/module/core/parts.hpp>
#include <fluxion/module/core/d.hpp>
#include <fluxion/module/core/convert.hpp>
#include <fluxion/module/core/pure.hpp>
#include <fluxion/module/core/if_else.hpp>
#include <fluxion/module/core/to_dual.hpp>
#include <fluxion/module/core/to_dual2.hpp>
#include <fluxion/module/core/to_dual3.hpp>
#include <fluxion/module/core/to_dual4.hpp>

//======================================================================================================================
// Arithmetic and predicates
//======================================================================================================================

#include <fluxion/module/core/add.hpp>
#include <fluxion/module/core/average.hpp>
#include <fluxion/module/core/dec.hpp>
#include <fluxion/module/core/div.hpp>
#include <fluxion/module/core/dot.hpp>
#include <fluxion/module/core/fam.hpp>
#include <fluxion/module/core/fma.hpp>
#include <fluxion/module/core/fms.hpp>
#include <fluxion/module/core/fnma.hpp>
#include <fluxion/module/core/fnms.hpp>
#include <fluxion/module/core/fsm.hpp>
#include <fluxion/module/core/horner.hpp>
#include <fluxion/module/core/inc.hpp>


#include <fluxion/module/core/is_equal.hpp>
#include <fluxion/module/core/is_eqz.hpp>
#include <fluxion/module/core/is_finite.hpp>
#include <fluxion/module/core/is_flint.hpp>
#include <fluxion/module/core/is_infinite.hpp>
#include <fluxion/module/core/is_nan.hpp>
#include <fluxion/module/core/is_nez.hpp>
#include <fluxion/module/core/is_not_denormal.hpp>
#include <fluxion/module/core/is_not_equal.hpp>
#include <fluxion/module/core/is_not_finite.hpp>
#include <fluxion/module/core/is_not_flint.hpp>
#include <fluxion/module/core/is_not_infinite.hpp>
#include <fluxion/module/core/is_not_nan.hpp>

#include <fluxion/module/core/ldiv.hpp>
#include <fluxion/module/core/lerp.hpp>
#include <fluxion/module/core/minus.hpp>
#include <fluxion/module/core/mul.hpp>
#include <fluxion/module/core/oneminus.hpp>
#include <fluxion/module/core/rec.hpp>
#include <fluxion/module/core/reverse_horner.hpp>
#include <fluxion/module/core/sub.hpp>
