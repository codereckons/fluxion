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

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_j1_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using v_t =  element_type_t<T>;
      x = abs(x);
      return average(cyl_bessel_j0(x), -cyl_bessel_jn(v_t(2), x));
    }
    else return apply_over(flx::derivative(cyl_bessel_j1), x);
  }
}
