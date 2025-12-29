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
  template< typename C, value U, value V, auto N>
  EVE_FORCEINLINE  auto binarize_(EVE_SUPPORTS(cpu_)
                                 , flx::derivative_type<N> const &
                                 , C const &
                                 , U const &
                                 , V const &) noexcept
  {
    using r_t =  eve::common_value_t<U, V>;
    return eve::zero(eve::as<r_t>());
  }
}
