//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr auto omega_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto omx = omega(x);
      return if_else(is_infinite(x), zero, omx/inc(omx));
    }
    else
      return apply_over(flx::derivative(omega), x);
  }
}
