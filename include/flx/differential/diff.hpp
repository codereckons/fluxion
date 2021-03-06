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
  // Function decorator - differential mode
  template<auto Param> struct diff_ {};

  template<auto Param> using diff_type = eve::decorated<diff_<Param>()>;

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<1> const diff      = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<1> const diff_1st  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<2> const diff_2nd  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<3> const diff_3rd  = {};

  //================================================================================================
  //! @ingroup differentials
  //================================================================================================
  template<auto N> inline constexpr diff_type<N> const diff_nth = diff_type<N>{};
}
