//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core.hpp>

#include <iosfwd>

namespace flx
{
  //====================================================================================================================
  //! @name Streaming Operators
  //! @related hyperdual
  //! @{
  //====================================================================================================================
  //! @brief Stream insertion for hyperdual based types
  //!
  //! Templated on the stream so that `<iosfwd>` is enough here: `<<` is only resolved where the
  //! operator is instantiated, which is wherever the caller already includes the real header.
  template<typename C, typename Ct, concepts::hyperdual CD>
  auto& operator<<(std::basic_ostream<C, Ct>& os, CD const& z)
  {
    constexpr char const* names[ 16 ]      = {"",
                                              "e1",
                                              "e2",
                                              "e12",
                                              "e3",
                                              "e13",
                                              "e23",
                                              "e123",
                                              "e4",
                                              "e14",
                                              "e24",
                                              "e34",
                                              "e124",
                                              "e134",
                                              "e234",
                                              "e1234"};

    auto                  display_positive = [](auto& out, auto e, bool first) -> decltype(auto)
    {
      if(first) return out << e;
      else if(eve::is_positive(e)) return out << " + " << e;
      else return out << " - " << -e;
    };

    kumi::for_each_index([ & ](auto i, auto v) { display_positive(os, v, i == 0) << names[ i ]; },
                         z);
    return os;
  }
  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
