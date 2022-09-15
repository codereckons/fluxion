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
  template<floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto beta_(EVE_SUPPORTS(cpu_)
                              , flx::diff_type<N> const &
                              , T const &a
                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(flx::diff_type<N>{}(beta), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T beta_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T const &x
                                  , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return -(digamma(x+y)-digamma(x))*beta(x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T beta_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<2> const &
                                  , T const &x
                                  , T const &y) noexcept
  requires(has_native_abi_v<T>)
  {
    return -(digamma(x + y)-digamma(y))*beta(x, y);
  }
}
