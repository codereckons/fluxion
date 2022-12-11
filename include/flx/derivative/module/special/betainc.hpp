//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_(EVE_SUPPORTS(cpu_)
                              , flx::derivative_type<N> const &
                              , S const &s
                              , T const &a
                              , U const &b) noexcept
  -> common_value_t<S, T, U>
  requires(std::floating_point<underlying_type_t<common_value_t<S, T, U>>>)
  {
    return arithmetic_call(flx::derivative_type<N>{}(betainc), s, a, b);
  }

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T betainc_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &s
                                   , T const &x
                                   , T const &y) noexcept
  requires(std::floating_point<underlying_type_t<T>>)
  {
    return pow(s, dec(x))*pow(oneminus(s), dec(y))/beta(x, y);
  }
}
