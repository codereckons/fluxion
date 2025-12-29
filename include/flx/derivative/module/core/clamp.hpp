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
  template<floating_ordered_value T, floating_ordered_value U, floating_ordered_value V, auto N>
  EVE_FORCEINLINE  auto clamp_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  ->common_value_t<T, U, V>
  {
    return arithmetic_call(flx::derivative_type<N>()(clamp), a, b, c);
  }

  template<floating_ordered_value T, auto N>
  EVE_FORCEINLINE  auto clamp_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(has_native_abi_v<T>)
  {
         if constexpr(N == 1) return flx::derivative_1st(min)(max(a, b), c)*flx::derivative_1st(max)(a, b);
    else if constexpr(N == 2) return flx::derivative_1st(min)(max(a, b), c)*flx::derivative_2nd(max)(a, b);
    else if constexpr(N == 3) return flx::derivative_2nd(min)(max(a, b), c);
  }
}
