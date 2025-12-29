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
  auto [s, c] = eve::sindcosd(r);
  T deg(1.745329251994330e-02);
  auto d0 = c;
  auto d1 = -s*deg;
  auto d2 = -c*deg*deg;
  auto d3 = s*deg*deg*deg;
  auto d4 = c*deg*deg*deg*deg;
  {
    auto vr = flx::variable<4>(r);
    auto cosdvr = flx::cosd(vr);
    TTS_ULP_EQUAL(flx::d0(cosdvr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(cosdvr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(cosdvr), d2, 1.5);
    TTS_ULP_EQUAL(flx::d3(cosdvr), d3, 1.5);
    TTS_ULP_EQUAL(flx::d4(cosdvr), d4, 1.5);
  }
};
