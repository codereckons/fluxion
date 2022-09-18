//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace flx
{
  //================================================================================================
  // Function decorator - derivative mode
  template<auto Param> struct derivative_ {};

  template<auto Param> using derivative_type = eve::decorated<derivative_<Param>()>;

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr derivative_type<1> const derivative      = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr derivative_type<1> const derivative_1st  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr derivative_type<2> const derivative_2nd  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr derivative_type<3> const derivative_3rd  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  template<auto N> inline constexpr derivative_type<N> const derivative_nth = derivative_type<N>{};
}
