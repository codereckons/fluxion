//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log2_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T const &x) noexcept
  {
    auto invlog2 = T(1.4426950408889634073599);
    return flx::diff(log)(x)*invlog2;
  }
}