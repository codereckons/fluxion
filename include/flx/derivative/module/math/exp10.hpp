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

  template<value T>
  EVE_FORCEINLINE constexpr T exp10_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x) noexcept
  {
    using elt_t = element_type_t<T>;
    auto constexpr l10 = elt_t(2.302585092994045684017);
    return exp10(x)*l10;
  }
}
