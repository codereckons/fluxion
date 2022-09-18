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

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T erfc_inv_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto sqrt_pi_2 = T(0.886226925452758013649);
      return -sqrt_pi_2*exp(sqr(erfc_inv(x)));
    }
    else
      return apply_over(flx::derivative(erfc_inv), x);
  }
}
