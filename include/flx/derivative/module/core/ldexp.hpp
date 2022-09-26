//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<floating_value T, value N>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x, N n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "some elements of n are not flint");
    return eve::ldexp(eve::one(as(x)), n);
  }

}
