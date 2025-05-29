//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/utils/derivatives.hpp>

namespace flx::_
{
  // given ders[0] compute derivative up to order using
  // proper functionnal definition of the first derivative
  template <auto I, auto Order, typename A, typename F, typename Hd, typename ...Zs> FLX_FORCEINLINE
  constexpr void dersfromderfunc(A & ders, F derfunc, Hd const& hd, Zs... zs) noexcept
  requires(ders.size() > Order)
  {
    auto dders = derivatives<0, Order>(derfunc, zs...);
    for(int i=1; i < Order; ++i)
    {
      ders[i] = dders[i-1];
    }
  }
  
}
