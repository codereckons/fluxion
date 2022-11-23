//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
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
      if constexpr(has_native_abi_v<T>)
      {
        return average(cyl_bessel_jn(dec(n), x), -cyl_bessel_jn(inc(n), x));
      }
      else return apply_over(flx::derivative_2nd(cyl_bessel_jn), n, x);
    }
    else return T(0);
  }
}
