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
// Perfect forwarding and function attributes, deferred to EVE so both libraries agree on what they
// mean.
#define FLX_FWD(...) EVE_FWD(__VA_ARGS__)
#define FLX_ABI      EVE_ABI
