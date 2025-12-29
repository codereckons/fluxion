//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/bessel.hpp>
#include <eve/module/bessel/regular/sph_bessel_yn.hpp>

namespace eve::detail
{

  template<auto N, ordered_value I, floating_ordered_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_yn_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , I nn
                                            , T x) noexcept
  {
    if constexpr(N == 2)
    {
      if constexpr(has_native_abi_v<T>)
      {
        auto n = eve::convert(nn, as<element_type_t<T>>());
        auto r = (n/x)*sph_bessel_yn(n, x) - sph_bessel_yn(inc(n), x);
        return if_else(is_not_nan(x) && is_nan(r), inf(as(r)), r);
      }
      else return apply_over(flx::derivative_2nd(sph_bessel_yn), nn, x);
    }
    else return T(0);
  }
}
