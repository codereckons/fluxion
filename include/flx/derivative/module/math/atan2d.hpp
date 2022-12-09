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

  template<value T, auto N>
  EVE_FORCEINLINE constexpr T atan2d_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
  {
    return radindeg(flx::derivative_type<N>()(atan2)(x, y));
  }

}
