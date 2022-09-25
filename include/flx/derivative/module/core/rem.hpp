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

  template<floating_value T, floating_value U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T , U  ) noexcept
  {
    using r_t = common_compatible_t<T, U>;
    return eve::one(as<r_t>());
  }

  template<floating_value T, floating_value U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<2> const &
                                    , T x, U y ) noexcept
  {
    using r_t = common_compatible_t<T, U>;
    return -eve::trunc(r_t(x)/r_t(y));
  }

}
