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
// two customisation points TTS looks up in the type's namespace.
//======================================================================================================================
namespace eve
{
  template<typename T, typename N>
  inline bool compare_equal(wide<T, N> const& l, wide<T, N> const& r)
  {
    return eve::all(l == r);
  }

  template<simd_value V> inline tts::text to_text(V const& v)
  {
    std::ostringstream os;
    os << v;
    return tts::text(os.str().c_str());
  }
}

namespace flx
{
  // The report only: equality of two hyperduals reads their value alone, which is the type's
  // decision to make, not the tests'.
  template<concepts::hyperdual T> inline tts::text to_text(T const& h)
  {
    std::ostringstream os;
    os << h;
    return tts::text(os.str().c_str());
  }

  using scalar_real_types = tts::types<float, double>;
  using simd_real_types   = tts::types<eve::wide<float>, eve::wide<double>>;
  using real_types        = tts::concatenate<scalar_real_types, simd_real_types>;
}
