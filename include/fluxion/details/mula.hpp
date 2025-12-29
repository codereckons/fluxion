//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/types/traits.hpp>
#include <array>

namespace flx::_
{
  // multiplies t[i] by a^i for i = 0 to Order
  template < auto Order, typename T0,  typename T1> FLX_FORCEINLINE
  constexpr void mul_by(std::array<T0, flx::max_order+1> & t, T1 const & a) noexcept
  {
    auto b = a;
    for(int i=1; i <= Order; ++i)
    {
      t[i] *= b;
      b *= a;
    }
  }

}
