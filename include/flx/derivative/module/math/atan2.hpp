//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T atan2_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return rec(sqr(x)+sqr(y))*y;
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T atan2_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return  rec(sqr(x)+sqr(y))*x;
  }
}
