//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"

#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::der
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::der(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10), tts::randoms(-10, +10)))
<typename T>(T const& a0, T const& /*a1*/)
{
  using flx::der;
  using flx::var;

  auto vda0 = var(a0);
  TTS_EQUAL(der(vda0), T{1});
};
