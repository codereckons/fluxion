//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{

  template<integral_value N, floating_real_value T>
  EVE_FORCEINLINE constexpr auto hermite_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  requires index_compatible_values<N, T>
  {
    return fma(x+x, eve::hermite(n, x), -eve::hermite(inc(n), x));
  }
}
