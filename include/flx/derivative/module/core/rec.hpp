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
  template<value T>
  EVE_FORCEINLINE constexpr auto rec_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return -sqr(rec(x));
    else
      return apply_over(flx::derivative(rec), x);
  }
}
