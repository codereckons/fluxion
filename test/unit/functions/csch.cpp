//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::csch over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T r)
{
  auto g = [](auto x){return 2*flx::rec(flx::exp(x)-flx::exp(-x)); };
  auto vr = flx::variable<4>(r);
  auto ref =  g(vr);
  {
    auto cschvr = flx::csch(vr);
    TTS_ULP_EQUAL(flx::d0(cschvr), flx::d0(ref), 0.5);
    TTS_ULP_EQUAL(flx::d1(cschvr), flx::d1(ref), 0.5);
    TTS_ULP_EQUAL(flx::d2(cschvr), flx::d2(ref), 0.5);
    TTS_ULP_EQUAL(flx::d3(cschvr), flx::d3(ref), 0.5);
    TTS_ULP_EQUAL(flx::d4(cschvr), flx::d4(ref), 0.5);
  }
};
