//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<auto N, floating_real_value T, real_value I>
  EVE_FORCEINLINE constexpr T exp_int_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<N> const &
                                  , I const &i
                                  , T const &x) noexcept
  {
    if constexpr(N == 2)
      return -exp_int(dec(i), x);
    else
      return T(0);
  }
}
