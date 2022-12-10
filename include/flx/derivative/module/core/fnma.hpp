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
  EVE_FORCEINLINE  auto fnma_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &c) noexcept
  -> common_value_t<T, U, V>
  requires(std::floating_point<underlying_type_t<common_value_t<T, U, V>>>)
  {
    return arithmetic_call(flx::derivative_type<N>{}(fnma), a, b, c);
  }

  template<value T, auto N>
  EVE_FORCEINLINE  auto fnma_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , T const &b
                            , T const &c) noexcept
  requires(std::floating_point<underlying_type_t<T>>)
  {
    if constexpr(N == 1) return minus(b);
    else if constexpr(N == 2) return minus(a);
    else if constexpr(N == 3) return one(as(c));
  }
}
