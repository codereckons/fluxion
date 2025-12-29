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
template<value T, value U, auto N>
EVE_FORCEINLINE  auto lbeta_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b) noexcept
->common_value_t<T, U>
requires(std::floating_point<underlying_type_t<common_value_t<T, U>>>)
{
  return arithmetic_call(flx::derivative_type<N>{}(lbeta), a, b);
}

template<value T>
EVE_FORCEINLINE constexpr T lbeta_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x
                                  , T const &y) noexcept
requires(std::floating_point<underlying_type_t<T>>)
{
  return digamma(x) - digamma(x + y);
}

template<value T>
EVE_FORCEINLINE constexpr T lbeta_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<2> const &
                                  , T const &x
                                  , T const &y) noexcept
requires(std::floating_point<underlying_type_t<T>>)
{
  return  digamma(y) - digamma(x + y);
}
}
