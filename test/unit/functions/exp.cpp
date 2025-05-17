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

TTS_CASE_WITH ( "Check flx::exp over hyperdual 1"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<1>(r);
  auto expr = flx::exp(vr);
  TTS_EQUAL(flx::e0(expr), eve::exp(r));
  TTS_EQUAL(flx::e1(expr), eve::exp(r));
};

TTS_CASE_WITH ( "Check flx::exp over hyperdual 2"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<2>(r);
  auto expr = flx::exp(vr);
  TTS_EQUAL(flx::d0(expr), eve::exp(r));
  TTS_EQUAL(flx::d1(expr), eve::exp(r));
  TTS_EQUAL(flx::d2(expr), eve::exp(r));
};

TTS_CASE_WITH ( "Check flx::exp over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<3>(r);
  auto expr = flx::exp(vr);
  TTS_ULP_EQUAL(flx::d0(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d1(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d2(expr), eve::exp(r), 0.5);
  TTS_ULP_EQUAL(flx::d3(expr), eve::exp(r), 0.5);
};
