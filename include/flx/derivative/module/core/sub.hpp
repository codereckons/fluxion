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
  template<auto N, value T, value... Ts>
  EVE_FORCEINLINE constexpr auto sub_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<N> const &
                                    , T, Ts ... ) noexcept
  requires(std::floating_point<underlying_type_t< common_value_t<T,Ts...>>>)
  {
    using r_t = common_value_t<T,Ts...>;
    if constexpr(N > sizeof...(Ts)+1) return zero(as < r_t>());
    else if constexpr(N == 1) return one(as<r_t>());
    else return mone(as<r_t>());
  }
}
