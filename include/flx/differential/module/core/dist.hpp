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
  EVE_FORCEINLINE constexpr T dist_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<1> const &
                                    , T x, T y) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return sign(x-y);
    else
      return apply_over(flx::diff_1st(dist), x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T dist_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<2> const &
                                    , T x, T y) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return sign(y-x);
    else
      return apply_over(flx::diff_2nd(dist), x, y);
  }
}
