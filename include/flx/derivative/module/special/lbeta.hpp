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
  template<floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto lbeta_(EVE_SUPPORTS(cpu_)
                              , flx::derivative_type<N> const &
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(flx::derivative_type<N>{}(lbeta), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T lbeta_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T const &x
                                    , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return digamma(x) - digamma(x + y);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr T lbeta_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<2> const &
                                  , T const &x
                                  , T const &y) noexcept
requires(has_native_abi_v<T>)
  {
    return  digamma(y) - digamma(x + y);
  }
}
