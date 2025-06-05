//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::tanh over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(0.5,5))
              )
  <typename T>(T r)
{
  auto g = [](auto x){return (flx::exp(x)-flx::exp(-x))*flx::rec(flx::exp(x)+flx::exp(-x)); };
  auto vr = flx::variable<4>(r);
  auto ref =  g(vr);
  {
    auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
    auto tanhvr = flx::tanh(vr);
    TTS_RELATIVE_EQUAL(flx::d0(tanhvr), flx::d0(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d1(tanhvr), flx::d1(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d2(tanhvr), flx::d2(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d3(tanhvr), flx::d3(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d4(tanhvr), flx::d4(ref), pr);
  }
};
