//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>

namespace eve::detail
{

  template<floating_value T>
  EVE_FORCEINLINE constexpr T agd_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return if_else(abs(x) <= pio_2(as(x)), sec(x), allbits);
  }

  template<value T>
  EVE_FORCEINLINE constexpr T agd_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T const &x) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return sec(x);
  }
}
