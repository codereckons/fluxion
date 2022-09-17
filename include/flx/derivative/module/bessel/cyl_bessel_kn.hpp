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

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_kn_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return -average(cyl_bessel_kn(dec(n), x), cyl_bessel_kn(inc(n), x));
    }
    else return apply_over(flx::derivative(cyl_bessel_kn), n, x);
   }
}
