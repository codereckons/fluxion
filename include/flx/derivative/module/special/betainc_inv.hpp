//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{
  template<floating_value S, floating_value T, floating_value U, auto N>
  EVE_FORCEINLINE  auto betainc_inv_(EVE_SUPPORTS(cpu_)
                              , flx::derivative_type<N> const &
                              , S const &s
                              , T const &x
                              , U const &y) noexcept
  {
    auto b = betainc_inv(s, x, y);
    return rec(flx::derivative_1st(betainc)(b, x, y));
  }
}
