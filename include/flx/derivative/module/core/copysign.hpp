//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<floating_ordered_value T, floating_ordered_value U, auto N>
  EVE_FORCEINLINE  auto copysign_(EVE_SUPPORTS(cpu_)
                                 , flx::derivative_type<N> const &
                                 , T const &
                                 , U const &b) noexcept
  {
    using v_t = common_value_t<T, U>;
    if constexpr(N == 1) return v_t(sign(b));
    else if constexpr(N == 2) return zero(as<v_t>());
  }
}
