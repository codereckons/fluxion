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
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                   , flx::diff_type<1> const &
                                   , T x
                                   , N n) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return if_else(is_eqz(n), dec(x), if_else(n == 1, one(as(x)), zero));
    }
    else
      return apply_over(flx::diff_1st(dec), x, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<1> const &
                                    , T x) noexcept
  {

    return one(as(x));
  }
}
