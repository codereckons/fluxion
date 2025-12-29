//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::cosh over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T r)
{
  auto [s, c] = eve::sinhcosh(r);
  {
    auto vr = flx::variable<1>(r);
    auto coshvr = flx::cosh(vr);
    TTS_ULP_EQUAL(flx::d0(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(coshvr),  s, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto coshvr = flx::cosh(vr);
    TTS_ULP_EQUAL(flx::d0(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(coshvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d2(coshvr),  c, 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto coshvr = flx::cosh(vr);
    TTS_ULP_EQUAL(flx::d0(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(coshvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d2(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d3(coshvr),  s, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto coshvr = flx::cosh(vr);
    TTS_ULP_EQUAL(flx::d0(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(coshvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d2(coshvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d3(coshvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d4(coshvr),  c, 0.5);
  }
};
