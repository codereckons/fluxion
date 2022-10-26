//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
  template<value T, value N>
  EVE_FORCEINLINE constexpr T nthroot_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T x, N n) noexcept
  {
    using elt_t = element_type_t<T>;
    auto tn = convert(n, as<elt_t>());
    return nthroot(x, n)*rec(x*tn);
  }
}
