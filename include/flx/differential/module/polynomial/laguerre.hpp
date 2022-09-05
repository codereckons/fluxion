//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<integral_real_value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::diff_type<1> const &
                                       , N const & n
                                       , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    return -laguerre(1, n, x);
  }

  template<integral_real_value M, integral_real_value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::diff_type<1> const &
                                       , M const & m
                                       , N const & n
                                       , T const &x) noexcept
  requires index_compatible_values<N, T> && index_compatible_values<M, T>
  {
    return if_else(is_eqz(n), zero, sign_alternate(m)*laguerre(inc(m), saturated(dec)(n), x));
  }
}
