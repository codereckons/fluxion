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

  template<eve::value T, eve::value U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T , U  ) noexcept
  {
    using r_t = common_value_t<T, U>;
    return one(as<r_t>());
  }

  template<value T, value U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<2> const &
                                    , T const &x, U const & y ) noexcept
  {
    return -eve::trunc(x/y);
  }

}
