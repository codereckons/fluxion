//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<1> const &
                                    , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return half(as(x))*rsqrt(x);
    else
      return apply_over(flx::diff_1st(sqrt), x );
  }
}
