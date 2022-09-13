//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/bessel.hpp>
#include <eve/module/bessel/regular/sph_bessel_yn.hpp>

namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_yn_(EVE_SUPPORTS(cpu_)
                                            , flx::diff_type<1> const &
                                            , I nn
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto n = eve::convert(nn, as<element_type_t<T>>());
      auto r = (n/x)*sph_bessel_yn(n, x) - sph_bessel_yn(inc(n), x);
      return if_else(is_not_nan(x) && is_nan(r), inf(as(r)), r);
    }
    else return apply_over(flx::diff(sph_bessel_yn), nn, x);
  }
}
