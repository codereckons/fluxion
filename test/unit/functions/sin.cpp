//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::sin over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto sinvr = flx::sin(vr);
  auto [s, c] = eve::sincos(r);
  TTS_ULP_EQUAL(flx::D0(sinvr),  s, 0.5);
  TTS_ULP_EQUAL(flx::D1(sinvr),  c, 0.5);
  TTS_ULP_EQUAL(flx::D2(sinvr), -s, 0.5);
  TTS_ULP_EQUAL(flx::D3(sinvr), -c, 0.5);
  TTS_ULP_EQUAL(flx::D4(sinvr),  s, 0.5);
};
