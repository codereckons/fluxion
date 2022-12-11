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
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<N> const &
                                    , T , Ts ... ys ) noexcept
  requires(std::floating_point<underlying_type_t< common_value_t<T,Ts...>>>)
  {
    using r_t = common_value_t<T,Ts...>;
    using elt_t = element_type_t<r_t>;
    return (N > sizeof...(Ts)+1) ? zero(as < r_t>()) : r_t(rec(elt_t(sizeof...(ys)+1)));
  }

}
