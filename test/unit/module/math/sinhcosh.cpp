//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::sinh over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(-5, 5))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto [sinhvr, coshvr] = flx::sinhcosh(vr);
  auto [s, c] = eve::sinhcosh(r);
  TTS_ULP_EQUAL(flx::d0(sinhvr), s, 0.5);
  TTS_ULP_EQUAL(flx::d1(sinhvr), c, 0.5);
  TTS_ULP_EQUAL(flx::d2(sinhvr), s, 0.5);
  TTS_ULP_EQUAL(flx::d3(sinhvr), c, 0.5);
  TTS_ULP_EQUAL(flx::d4(sinhvr), s, 0.5);
  TTS_ULP_EQUAL(flx::d0(coshvr), c, 0.5);
  TTS_ULP_EQUAL(flx::d1(coshvr), s, 0.5);
  TTS_ULP_EQUAL(flx::d2(coshvr), c, 0.5);
  TTS_ULP_EQUAL(flx::d3(coshvr), s, 0.5);
  TTS_ULP_EQUAL(flx::d4(coshvr), c, 0.5);
};
