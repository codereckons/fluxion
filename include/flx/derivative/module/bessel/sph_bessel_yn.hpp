//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/bessel.hpp>
#include <eve/module/bessel/regular/sph_bessel_yn.hpp>

namespace eve::detail
{

  template<auto N, real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_yn_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , I nn
                                            , T x) noexcept
  {
    if constexpr(N == 2)
    {
      EVE_ASSERT(eve::all(eve:is_flint(n)), "some n are not flint");
      auto n = eve::convert(nn, eve::as<eve::element_type_t<T>>()) ;
      if constexpr(has_native_abi_v<T>)
      {
        auto r = (n/x)*sph_bessel_yn(n, x) - sph_bessel_yn(inc(n), x);
        return if_else(is_not_nan(x) && is_nan(r), inf(as(r)), r);
      }
      else return apply_over(flx::derivative_2nd(sph_bessel_yn), nn, x);
     }
    else
    {
      EVE_ASSERT( N == 2, "sph_bessel_yn derivative is only implemented relative to second parameter");
      using r_t = decltype(eve::sph_bessel_yn(nn, x));
      return eve::nan(eve::as<r_t>());
    }
  }
}
