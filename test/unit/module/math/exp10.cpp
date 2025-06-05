//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::exp10 over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::exp10(data), eve::exp10(data));
};


TTS_CASE_WITH ( "Check flx::exp10 over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto exp10r = flx::exp10(vr);
  auto l10 =  eve::log_10(eve::as<T>());
  auto l10s = l10;
  TTS_ULP_EQUAL(flx::d0(exp10r), eve::exp10(r), 0.5);
  TTS_ULP_EQUAL(flx::d1(exp10r), l10s*eve::exp10(r), 0.5);
  l10s *= l10;
  TTS_ULP_EQUAL(flx::d2(exp10r), l10s*eve::exp10(r), 0.5);
  l10s *= l10;
  TTS_ULP_EQUAL(flx::d3(exp10r), l10s*eve::exp10(r), 0.5);
  l10s *= l10;
  TTS_ULP_EQUAL(flx::d4(exp10r), l10s*eve::exp10(r), 0.5);
};
