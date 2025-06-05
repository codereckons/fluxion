//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::gd over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(0.5,20))
              )
  <typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto ref =  flx::sech(vr);
  {
    auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
    auto gdvr = flx::gd(vr);
    TTS_RELATIVE_EQUAL(flx::d0(gdvr), flx::gd(r), pr);
    TTS_RELATIVE_EQUAL(flx::d1(gdvr), flx::d0(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d2(gdvr), flx::d1(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d3(gdvr), flx::d2(ref), pr);
    TTS_RELATIVE_EQUAL(flx::d4(gdvr), flx::d3(ref), pr);
  }
};
