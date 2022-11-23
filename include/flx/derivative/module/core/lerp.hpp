//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<value T, value U, value V, auto N>
  EVE_FORCEINLINE  auto lerp_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &t) noexcept
  requires compatible_values<T, U>&&compatible_values<T, V>
  {
    return arithmetic_call(flx::derivative_type<N>()(lerp), a, b, t);
  }

  template<value T, auto N>
  EVE_FORCEINLINE  auto lerp_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &t) noexcept
  requires(has_native_abi_v<T>)
  {
    if constexpr(N == 1) return oneminus(t);
    else if constexpr(N == 2) return t;
    else if constexpr(N == 3) return b-a;
  }
}
