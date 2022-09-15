//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T erf_inv_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto sqrt_pi_2 = T(0.886226925452758013649);
      return sqrt_pi_2*exp(sqr(erf_inv(x)));
    }
    else
      return apply_over(flx::diff(erf_inv), x);
  }
}
