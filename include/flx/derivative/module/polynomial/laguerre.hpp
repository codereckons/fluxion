//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{


  template<auto I, value M, value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::derivative_type<I> const &
                                       , M const & m
                                       , N const & n
                                       , T const &x) noexcept
  {
    EVE_ASSERT(eve::all(eve:is_flint(m)), "some m are not flint");
    EVE_ASSERT(eve::all(eve:is_flint(n)), "some n are not flint");

    return if_else(is_eqz(n), zero, sign_alternate(m)*laguerre(inc(m), saturated(dec)(n), x));
  }

  template<auto I, value N, floating_value T>
  EVE_FORCEINLINE constexpr T laguerre_(EVE_SUPPORTS(cpu_)
                                       , flx::derivative_type<I> const &
                                       , N const & n
                                       , T const &x) noexcept
  {
    using e_t = element_type_t<T>;
    if constexpr(I == 2)
    {
      auto nn = int_(n);
      EVE_ASSERT(eve::all(eve:is_flint(n)), "some n are not flint");
      return -laguerre(one(as(nn)), nn, x);
    }
    else
    {
      EVE_ASSERT( I == 2, "laguerre derivative is only implemented relative to second parameter");
      using r_t = common_compatible_t<T, decltype(convert(n, as<e_t>()))>;
      return eve::nan(eve::as<r_t>());
    }
  }

}
