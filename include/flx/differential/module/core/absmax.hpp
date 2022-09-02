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
  template<int N, typename T0, typename T1, typename... Ts>
  auto absmax_(EVE_SUPPORTS(cpu_), flx::diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return minmax_kernel<N>(eve::max, eve::sign, arg0, arg1, args...);
  }
}
