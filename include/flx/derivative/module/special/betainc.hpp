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
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_(EVE_SUPPORTS(cpu_)
                              , flx::derivative_type<N> const &
                              , S const &s
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U> && compatible_values<T, S>
  {
    return arithmetic_call(flx::derivative_type<N>{}(betainc), s, a, b);
  }

  template<floating_real_value T, auto N>
  EVE_FORCEINLINE constexpr T betainc_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<N> const &
                                   , T const &s
                                   , T const &x
                                   , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N != 1) return zero(eve::as<T>());
    else return pow(s, dec(x))*pow(oneminus(s), dec(y))/beta(x, y);
  }
}
