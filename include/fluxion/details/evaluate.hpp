//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/compose.hpp>
#include <fluxion/types/traits.hpp>
#include <array>

namespace flx::_
{
  //evaluate using prepared derivatives
  template <concepts::hyperdual Z> FLX_FORCEINLINE
  constexpr auto evaluate(auto const & ders, Z const & z) noexcept
  {
    if constexpr(flx::order_v<Z> == 1)
    {
      return Z(ders[0], ders[1]*e1(z));
    }
    else if constexpr(flx::order_v<Z> == 2)
    {
      return chain(z, ders[0], ders[1], ders[2]);
    }
    else if constexpr(flx::order_v<Z> == 3)
    {
      return chain(z, ders[0], ders[1], ders[2], ders[3]);
    }
//       else if constexpr(flx::order_v<Z> == 4)
//       {
//         return chain(z, ders[0], ders[1], ders[2], ders[3], ders[4]);
//       }
    else
    {
      return taylor(z, ders);
    }
  }

}
