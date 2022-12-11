//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{

  template<integral_value N, value T>
  EVE_FORCEINLINE constexpr auto hermite_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  ->indexed_common_value_t<N, T>
  {
    using f_t = indexed_common_value_t<N, T>;
    auto nn(to_<f_t>(n));
    return fma(x+x, eve::hermite(nn, x), -eve::hermite(inc(nn), x));
  }
}
