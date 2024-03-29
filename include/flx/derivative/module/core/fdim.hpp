//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_ordered_value T, floating_ordered_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T x
                                    , U y) noexcept
  -> common_value_t<T, U>
  {
    using r_t = common_value_t<T,U>;
    return if_else(is_not_less(x, y), one(as<r_t>()), zero);
  }

  template<floating_ordered_value T, floating_ordered_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<2> const &
                                    , T x
                                    , U y) noexcept
  -> common_value_t<T, U>
  {
    using r_t = common_value_t<T,U>;
    return if_else(is_not_less(x, y), mone(as<r_t>()), zero);
  }
}
