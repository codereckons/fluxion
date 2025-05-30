//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::expm1 over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::expm1(data), eve::expm1(data));
};


TTS_CASE_WITH ( "Check flx::expm1 over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto expm1r = flx::expm1(vr);
  TTS_ULP_EQUAL(flx::d0(expm1r), eve::expm1(r), 0.5);
  TTS_ULP_EQUAL(flx::d1(expm1r), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d2(expm1r), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d3(expm1r), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d4(expm1r), eve::exp(r), 0.5);
};
