//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE constexpr T atan2_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return rec(sqr(x)+sqr(y))*y;
  }

  template<value T>
  EVE_FORCEINLINE constexpr T atan2_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return  rec(sqr(x)+sqr(y))*x;
  }
}
