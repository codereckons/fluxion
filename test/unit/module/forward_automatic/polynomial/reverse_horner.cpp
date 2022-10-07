//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::reverse_horner
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::reverse_horner(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::reverse_horner(vda0, a1))          , eve::reverse_horner(a0, a1), 0.5);
  TTS_ULP_EQUAL(der(eve::reverse_horner(vda0, a1))          , derivative(eve::reverse_horner)(a0, a1), 0.5);
  TTS_ULP_EQUAL(val(eve::reverse_horner(vda0, a1, a2))      , eve::reverse_horner(a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(der(eve::reverse_horner(vda0, a1, a2))      , derivative(eve::reverse_horner)(a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(val(eve::reverse_horner(vda0, a1, a2, a3))  , eve::reverse_horner(a0, a1, a2, a3), 0.5);
  TTS_ULP_EQUAL(der(eve::reverse_horner(vda0, a1, a2, a3))  , derivative(eve::reverse_horner)(a0, a1, a2, a3), 0.5);
};
