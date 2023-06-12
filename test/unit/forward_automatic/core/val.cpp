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
// Tests for flx::val
//==================================================================================================
TTS_CASE_WITH("Check behavior of flx::val(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, +10), tts::randoms(-10, +10)))
(auto const& a0, auto const& /*a1*/)
{
  using flx::val;
  using flx::var;

  auto vda0 = var(a0);
  TTS_EQUAL(val(vda0), a0);
};
