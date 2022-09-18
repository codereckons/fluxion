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
  template<auto N, floating_real_value T, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr T average_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<N> const &
                                    , T , Ts ... ys ) noexcept
  {
    using r_t = common_compatible_t<T,Ts...>;
    using elt_t = element_type_t<r_t>;
    return (N > sizeof...(Ts)+1) ? zero(as < r_t>()) : r_t(rec(elt_t(sizeof...(ys)+1)));
  }

}
