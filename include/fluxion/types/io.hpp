//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <string>

namespace flx
{
  //====================================================================================================================
  //! @name Streaming Operators
  //! @related hyperdual
  //! @{
  //====================================================================================================================

  /// Stream insertion for hyperdual based types
  template<concepts::hyperdual CD>
  std::ostream& operator<<(std::ostream& os, CD const& z)
  {
    static constexpr
      std::array<char *, 16> names = {  "",   "e1"
                                      , "e2", "e12"
                                      , "e3", "e13", "e23", "e123"
                                      , "e4", "e14", "e24", "e34", "e124", "e134", "e234", "e1234"};

    auto display_positive = [](std::ostream& os,auto e, bool first) -> std::ostream& {
      if(first)                     return os << e;
      else if(eve::is_positive(e))  return os << " + " << e;
      else                          return os << " - " << -e;
    };

    kumi::for_each_index([&](auto i, auto v) { display_positive(os,v,i == 0) << names[i];}, z);
    return os;
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
