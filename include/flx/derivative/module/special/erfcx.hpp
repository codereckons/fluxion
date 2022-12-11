//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE constexpr T erfcx_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                  , T const &x) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    auto twoosqrtpi = underlying_type_t<T>(1.1283791670955125738961589);
    return fms(2*x, erfcx(x),  twoosqrtpi);
  }
}
