//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#define TTS_MAIN
#include <fluxion/fluxion.hpp>
#include <tts/tts.hpp>

#include <sstream>

//======================================================================================================================
// A wide answers a logical rather than a bool, and prints through its own inserter, so it needs the
// two traits TTS reads for a type it does not know.
//======================================================================================================================
namespace tts
{
  template<typename T, typename N> struct comparison<eve::wide<T, N>, eve::wide<T, N>>
  {
    static bool equal(eve::wide<T, N> const& l, eve::wide<T, N> const& r)
    {
      return eve::all(l == r);
    }
  };

  // The report only: equality of two hyperduals reads their value alone, which is the type's
  // decision to make, not the tests'.
  template<typename T>
    requires(eve::simd_value<T> || flx::concepts::hyperdual<T>) // a wide of hyperduals is both
  struct display<T>
  {
    static text render(T const& v)
    {
      std::ostringstream os;
      os << v;
      return text(os.str().c_str());
    }
  };
}

namespace flx
{
  using scalar_real_types = tts::types<float, double>;
  using simd_real_types   = tts::types<eve::wide<float>, eve::wide<double>>;
  using real_types        = tts::concatenate<scalar_real_types, simd_real_types>;
}
