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

  template<value T>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T x) noexcept
  {
    return zero(as(x));
  }

// HAVE WE DO DEFINE THIS ?
// ALL THE WAY IT DOES NOT WORK
//   template<eve::conditional_expr C, value T>
//   EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
//                                    , flx::derivative_type<1> const & d
//                                    , C cond
//                                    , T x) noexcept
//   {
//     return  mask_op(cond, d(eve::floor), x);
//   }


}
