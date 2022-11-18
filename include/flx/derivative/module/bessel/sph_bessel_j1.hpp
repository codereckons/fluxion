//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/bessel.hpp>
#include <flx/derivative/module/bessel/sph_bessel_jn.hpp>

namespace eve::detail
{


  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_j1_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T x) noexcept
  {
    return flx::derivative(sph_bessel_jn)(1, x);
  }
}
