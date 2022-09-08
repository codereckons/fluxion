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

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , flx::diff_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      EVE_ASSERT(all(is_gez(n) && is_flint(n)), "flx::diff(sph_bessel_jn) : some orders are non integral positive");
      EVE_ASSERT(all(is_nltz(x)),               "flx::diff(sph_bessel_jn) : some x are negative");
      auto nph = convert(n, as<element_type_t<T>>())+half(as(x));
      auto d = rsqrt(2*x*inv_pi(as(x)));
      return if_else( abs(x) < eps(as(x))
                    ,  if_else(is_eqz(n),  zero, inf(as(x)))
                    , (cyl_bessel_jn(nph, x)*mhalf(as(x))/x+flx::diff(cyl_bessel_jn)(nph, x))*d
                    );
    }
    else return apply_over(flx::diff(sph_bessel_jn), n, x);
   }
}
