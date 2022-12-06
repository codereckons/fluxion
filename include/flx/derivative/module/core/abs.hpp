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
  template<floating_ordered_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), abs(x),
                     if_else((n ==  one(as(n))), sign(x), zero));
    }
    else
      return apply_over(flx::derivative_1st(abs), x, n);
  }

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x) noexcept
  {

    return sign(x);
  }
}
