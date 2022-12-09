//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE constexpr kumi::tuple<T, T>
  sinhcosh_(EVE_SUPPORTS(cpu_), flx::derivative_type<1> const &, T x) noexcept
   {
    if constexpr( has_native_abi_v<T> )
    {
      auto [s, c] = sinhcosh(x);
      return {c, s};
    }
    else
    {
      return apply_over2(flx::derivative(sinhcosh), x);
    }
  }

}
