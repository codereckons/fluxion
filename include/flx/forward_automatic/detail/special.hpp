//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <flx/derivative/derivatives.hpp>
#include <flx/forward_automatic/is_derivable.hpp>
#include <flx/forward_automatic/der.hpp>
#include <flx/forward_automatic/val.hpp>

#include <eve/module/special.hpp>

// Those functions have a specific derivation specified here
template<> struct flx::has_optimized_derivative<eve::tag::lambert_>  : std::true_type {};

namespace flx::detail
{
   template<typename Z>
   EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::lambert_
                                              , Z const& z ) noexcept
   {
     auto [v, d] = z;
     auto [s, c]= eve::lambert(v);
     auto [ds, dc]= flx::derivative(eve::lambert)(v);
     return kumi::tuple{Z{s, d*ds}, Z{c, d*dc}};
   }

}
