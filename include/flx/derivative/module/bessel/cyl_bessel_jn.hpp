//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/bessel.hpp>

namespace eve::detail
{

  template<auto N, real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(N == 2)
    {
      EVE_ASSERT(eve::all(eve::is_flint(n)), "some n are not flint");
      auto nn = eve::convert(n, eve::as<eve::element_type_t<T>>()) ;
      if constexpr(has_native_abi_v<T>)
      {
        return average(cyl_bessel_jn(dec(nn), x), -cyl_bessel_jn(inc(nn), x));
      }
      else return apply_over(flx::derivative_2nd(cyl_bessel_jn), nn, x);
    }
    else
    {
      EVE_ASSERT( N == 2, "cyl_bessel_jn derivative is only implemented relative to second parameter");
      using r_t = decltype(eve::cyl_bessel_in(n, x));
      return eve::nan(eve::as<r_t>());
    }
  }
}
