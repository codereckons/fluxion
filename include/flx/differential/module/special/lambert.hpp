//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto lambert_(EVE_SUPPORTS(cpu_)
                                  , flx::diff_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto [w0, wm1] = lambert(x);
      auto xeqz = is_eqz(x);
      auto dw0 = if_else(w0 == mone(as(w0)), inf(as(w0)), w0/(x*inc(w0)));
      dw0 = if_else(x  == inf(as(x)), zero, dw0);
      dw0 = if_else(xeqz, one, dw0);
      auto dwm1= if_else(wm1 == mone(as(w0)), minf(as(w0)), wm1/(x*inc(wm1)));
      dwm1= if_else(is_gez(x), dw0, dwm1);
      dwm1= if_else(xeqz&&is_negative(x), minf(as(wm1)), dwm1);
      return kumi::make_tuple(dw0, dwm1);
    }
    else
      return apply_over2(flx::diff(lambert), x);
  }
}
