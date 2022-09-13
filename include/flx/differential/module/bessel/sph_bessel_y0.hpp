//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <flx/differential/module/bessel/sph_bessel_yn.hpp>
#include <eve/module/bessel.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_y0_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T const &x) noexcept
  {
    return flx::diff(sph_bessel_yn)(0u, x);
  }
}
