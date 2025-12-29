//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sinh over hyperduals "
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T r)
{
  auto [s, c] = eve::sinhcosh(r);
  {
    auto vr = flx::variable<1>(r);
    auto sinhvr = flx::sinh(vr);
    TTS_ULP_EQUAL(flx::d0(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d1(sinhvr),  c, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto sinhvr = flx::sinh(vr);
    TTS_ULP_EQUAL(flx::d0(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d1(sinhvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d2(sinhvr),  s, 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto sinhvr = flx::sinh(vr);
    TTS_ULP_EQUAL(flx::d0(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d1(sinhvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d2(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d3(sinhvr),  c, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto sinhvr = flx::sinh(vr);
    TTS_ULP_EQUAL(flx::d0(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d1(sinhvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d2(sinhvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d3(sinhvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d4(sinhvr),  s, 0.5);
  }
};
