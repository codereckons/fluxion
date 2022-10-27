//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<auto N, value T, value M>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<N> const &
                                    , T x, M n) noexcept
  {
    EVE_ASSERT( N == 1, "ldexp derivative is only implemented relative to first parameter");
    EVE_ASSERT(eve::all(is_flint(n)), "some elements of the second parameter are not flint");
    if constexpr(N == 1)
      return eve::ldexp(eve::one(as(x)), n);
    else
      return eve::nan(eve::as(x));
  }

}
