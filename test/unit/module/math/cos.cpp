//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::cos over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T r)
{
  auto [s, c] = eve::sincos(r);
  {
    auto vr = flx::variable<1>(r);
    auto cosvr = flx::cos(vr);
    TTS_ULP_EQUAL(flx::d0(cosvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(cosvr), -s, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto cosvr = flx::cos(vr);
    TTS_ULP_EQUAL(flx::d0(cosvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(cosvr), -s, 0.5);
    TTS_ULP_EQUAL(flx::d2(cosvr), -c, 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto cosvr = flx::cos(vr);
    TTS_ULP_EQUAL(flx::d0(cosvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(cosvr), -s, 0.5);
    TTS_ULP_EQUAL(flx::d2(cosvr), -c, 0.5);
    TTS_ULP_EQUAL(flx::d3(cosvr),  s, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto cosvr = flx::cos(vr);
    TTS_ULP_EQUAL(flx::d0(cosvr),  c, 0.5);
    TTS_ULP_EQUAL(flx::d1(cosvr), -s, 0.5);
    TTS_ULP_EQUAL(flx::d2(cosvr), -c, 0.5);
    TTS_ULP_EQUAL(flx::d3(cosvr),  s, 0.5);
    TTS_ULP_EQUAL(flx::d4(cosvr),  c, 0.5);
  }
};
