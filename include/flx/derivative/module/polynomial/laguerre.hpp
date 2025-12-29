//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{


  template<integral_value M, integral_value N, value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::derivative_type<1> const &
                                       , M const & m
                                       , N const & n
                                       , T const &x) noexcept
  {
    return if_else(is_eqz(n), zero, sign_alternate(m)*eve::laguerre(inc(m), saturated(dec)(n), x));
  }

  template<integral_value N, value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::derivative_type<1> const &
                                       , N const & n
                                       , T const &x) noexcept
  {
    return -eve::laguerre(one(as(n)), n, x);
  }

}
