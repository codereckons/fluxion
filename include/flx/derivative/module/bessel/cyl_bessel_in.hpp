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

  template<auto N, ordered_value I, floating_ordered_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_in_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(N == 2)
    {
      if constexpr(has_native_abi_v<T>)
      {
        return average(cyl_bessel_in(dec(n), x), cyl_bessel_in(inc(n), x));
      }
      else return apply_over(flx::derivative_2nd(cyl_bessel_in), n, x);
    }
    else return T(0);
  }
}
