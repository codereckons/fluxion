//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sech over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(0.5,20))
              )
  <typename T>(T r)
{
  auto g = [](auto x){return 2*flx::rec(flx::exp(x)+flx::exp(-x)); };
  auto vr = flx::variable<4>(r);
  auto ref =  g(vr);
  {
    auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
    auto sechvr = flx::sech(vr);
    TTS_RELATIVE_EQUAL(flx::d0(sechvr), flx::d0(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d1(sechvr), flx::d1(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d2(sechvr), flx::d2(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d3(sechvr), flx::d3(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d4(sechvr), flx::d4(ref), pr);
  }
};
