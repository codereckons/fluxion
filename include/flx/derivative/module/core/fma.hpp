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
  template<floating_value T, floating_value U, floating_value V, auto N>
  EVE_FORCEINLINE  auto fma_(EVE_SUPPORTS(cpu_)
                            , flx::derivative_type<N> const &
                            , T const &a
                            , U const &b
                            , V const &) noexcept
  {
    using r_t =  common_compatible_t<T, U, V>;
    if constexpr(N == 1) return r_t(b);
    else if constexpr(N == 2) return r_t(a);
    else if constexpr(N == 3) return one(as<r_t>());
  }
}
