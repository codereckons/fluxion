//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <type_traits>

namespace flx
{
  template<typename Tag> struct is_derivable              : std::true_type {};
  template<typename Tag> struct has_optimized_derivative  : std::false_type {};

  template<typename Tag>
  inline constexpr auto is_derivable_v =  is_derivable<Tag>::value;

  template<typename Tag>
  inline constexpr auto has_optimized_derivative_v =  has_optimized_derivative<Tag>::value;
}
