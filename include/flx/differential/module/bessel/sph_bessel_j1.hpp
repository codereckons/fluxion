//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/bessel.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_j1_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      //$B!](B2sin(x)/x^3+2cos(x)/x^2+sin(x)/x
      auto [s, c] = sincos(x);
      auto sq =  sqr(x);
      return if_else(x == inf(as(x))
                    , zero
                    , if_else(abs(x) < eps(as(x))
                             , inf(as(x))
                             , fma(sq-2, s, 2*x*c)/(sq*x)
                             )
                    );
    }
    else return apply_over(flx::diff(sph_bessel_j1), x);
  }
}