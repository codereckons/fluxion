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
  EVE_FORCEINLINE constexpr auto gamma_p_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x
                                  , T const &k) noexcept
  {
    return exp(dec(k) * log(x) - x - log_gamma(k));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto gamma_p_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<2> const &
                                  , T const &x
                                  , T const &k) noexcept
  {
    using r_t = decltype(gamma_p(x, k));
    return eve::zero(as<r_t>());
  }
}
