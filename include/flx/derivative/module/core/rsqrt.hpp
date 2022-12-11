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
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x) noexcept
  requires(std::floating_point<underlying_type_t<T>>)
  {
    if constexpr( has_native_abi_v<T> )
      return mhalf(as(x))*rec(sqrt(x)*x);
    else
      return apply_over(flx::derivative_1st(rsqrt), x);

  }
}
