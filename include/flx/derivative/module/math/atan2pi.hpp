//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<value T, auto N>
  EVE_FORCEINLINE constexpr T atan2pi_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<N> const &
                                   , T const &x
                                   , T const &y) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return radinpi(flx::derivative_type<N>()(atan2)(x, y));
  }

}
