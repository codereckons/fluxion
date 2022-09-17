//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<floating_real_value T, real_value N>
  EVE_FORCEINLINE constexpr T exp_int_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    return -exp_int(dec(n), x);
  }
}
