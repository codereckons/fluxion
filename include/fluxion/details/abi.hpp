//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

// Faster than std::forward
#define FLX_FWD(...)    EVE_FWD(__VA_ARGS__)
#define FLX_FORCEINLINE EVE_FORCEINLINE
