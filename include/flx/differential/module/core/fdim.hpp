//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<1> const &
                                    , T x
                                    , U y) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T,U>;
    return if_else(is_not_less(x, y), one(as<r_t>()), zero);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , flx::diff_type<2> const &
                                    , T x
                                    , U y) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T,U>;
    return if_else(is_not_less(x, y), mone(as<r_t>()), zero);
  }
}
