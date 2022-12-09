//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow_abs(x, dec(y))*y;
  }

   template<value T>
  EVE_FORCEINLINE constexpr T pow_abs_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return pow_abs(x, y)*log_abs(x);
  }
}
