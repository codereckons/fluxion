//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/core.hpp>
#include <flx/derivative/module/core/detail/minmax_kernel.hpp>

namespace eve::detail
{
  template<auto N, typename T0, typename T1, typename... Ts>
  auto absmax_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using v_t =  eve::common_compatible_t<T0, T1, Ts...>;
    return minmax_kernel<N>(eve::max, eve::sign, v_t(arg0), v_t(arg1), v_t(args)...);
  }
}
