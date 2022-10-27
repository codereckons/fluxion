//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<value T, value U, auto N>
  EVE_FORCEINLINE  auto copysign_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b) noexcept
  {
    using v_t = common_compatible_t<T, U>;
    if constexpr(N == 1) return v_t(sign(a))*v_t(sign(b));
    else if constexpr(N == 2) return zero(as<v_t>());
  }
}
