//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/abi.hpp>
#include <eve/traits/overload.hpp>

namespace flx::_    { EVE_CALLABLE_NAMESPACE(); }

//  EVE-related macro that use flx::_ as the deferred namespace
#define flx_CALLABLE_OBJECT(TYPE, NAME) EVE_CALLABLE_OBJECT_FROM(flx::_,TYPE, NAME)
#define flx_CALL(...)                   EVE_DISPATCH_CALL(__VA_ARGS__)
#define flx_DELAY()                     EVE_REQUIRES(eve::cpu_)
