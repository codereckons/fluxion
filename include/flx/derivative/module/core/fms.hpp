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
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(flx::derivative_type<N>()(fms), a, b, c);
  }

  template<floating_value T, auto N>
  EVE_FORCEINLINE  auto fms_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return b;
    else if constexpr(N == 2) return a;
    else if constexpr(N == 3) return mone(as(c));
  }
}
