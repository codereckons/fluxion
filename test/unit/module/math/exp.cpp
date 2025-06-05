//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::exp over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::exp(data), eve::exp(data));
};


TTS_CASE_WITH ( "Check flx::exp over hyperdual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto expr = flx::exp(vr);
  TTS_ULP_EQUAL(flx::d0(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d1(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d2(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d3(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d4(expr), eve::exp(r), 0.5);
};
