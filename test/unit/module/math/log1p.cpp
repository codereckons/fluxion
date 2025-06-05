//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::log1p over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,2))
              )
<typename T>(T r)
{
  auto d0 = eve::log1p(r);
  auto g = [](auto x){ return flx::rec(1+x); };
  auto vr = flx::variable<4>(r);
  auto dref = g(vr);
  auto log1pvr = flx::log1p(vr);
  TTS_ULP_EQUAL(flx::d0(log1pvr), d0, 2.5);
  TTS_ULP_EQUAL(flx::d1(log1pvr), flx::d0(dref), 2.5);
  TTS_ULP_EQUAL(flx::d2(log1pvr), flx::d1(dref), 3.0);
  TTS_ULP_EQUAL(flx::d3(log1pvr), flx::d2(dref), 3.0);
  TTS_ULP_EQUAL(flx::d4(log1pvr), flx::d3(dref), 3.5);
};
