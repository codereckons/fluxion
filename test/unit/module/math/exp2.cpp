//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::exp2 over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::exp2(data), eve::exp2(data));
};


TTS_CASE_WITH ( "Check flx::exp2 over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto exp2r = flx::exp2(vr);
  auto l2 =  eve::log_2(eve::as<T>());
  auto l2s = l2;
  TTS_ULP_EQUAL(flx::d0(exp2r), eve::exp2(r), 0.5);
  TTS_ULP_EQUAL(flx::d1(exp2r), l2s*eve::exp2(r), 0.5);
  l2s *= l2;
  TTS_ULP_EQUAL(flx::d2(exp2r), l2s*eve::exp2(r), 0.5);
  l2s *= l2;
  TTS_ULP_EQUAL(flx::d3(exp2r), l2s*eve::exp2(r), 0.5);
  l2s *= l2;
  TTS_ULP_EQUAL(flx::d4(exp2r), l2s*eve::exp2(r), 0.5);
};
