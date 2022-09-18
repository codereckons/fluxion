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
  EVE_FORCEINLINE constexpr T cyl_bessel_i1_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x) noexcept
  {
    return average(cyl_bessel_in(T(2), x), cyl_bessel_i0(x));
  }
}
