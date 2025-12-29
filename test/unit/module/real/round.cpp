//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_WITH ( "Check flx::round over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_EQUAL(flx::round(data), eve::round(data));
};

TTS_CASE_WITH ( "Check flx::round over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto d0   = eve::round(r);
  auto d1 = T(0);
  auto d2 = T(0);
  auto d3 = T(0);
  auto d4 = T(0);

  {
    auto vr = flx::variable<4>(r);
    auto roundvr = flx::round[eve::upward](vr);
    TTS_ULP_EQUAL(flx::d0(roundvr), d0, 0.5);
    TTS_ULP_EQUAL(flx::d1(roundvr), d1, 0.5);
    TTS_ULP_EQUAL(flx::d2(roundvr), d2, 0.5);
    TTS_ULP_EQUAL(flx::d3(roundvr), d3, 0.5);
    TTS_ULP_EQUAL(flx::d4(roundvr), d4, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto roundvr = flx::round[eve::downward](vr);
    TTS_ULP_EQUAL(flx::d0(roundvr), d0, 0.5);
    TTS_ULP_EQUAL(flx::d1(roundvr), d1, 0.5);
    TTS_ULP_EQUAL(flx::d2(roundvr), d2, 0.5);
    TTS_ULP_EQUAL(flx::d3(roundvr), d3, 0.5);
    TTS_ULP_EQUAL(flx::d4(roundvr), d4, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto roundvr = flx::round[eve::to_nearest](vr);
    TTS_ULP_EQUAL(flx::d0(roundvr), d0, 0.5);
    TTS_ULP_EQUAL(flx::d1(roundvr), d1, 0.5);
    TTS_ULP_EQUAL(flx::d2(roundvr), d2, 0.5);
    TTS_ULP_EQUAL(flx::d3(roundvr), d3, 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto roundvr = flx::round[eve::toward_zero](vr);
    TTS_ULP_EQUAL(flx::d0(roundvr), d0, 0.5);
    TTS_ULP_EQUAL(flx::d1(roundvr), d1, 0.5);
    TTS_ULP_EQUAL(flx::d2(roundvr), d2, 0.5);
    TTS_ULP_EQUAL(flx::d3(roundvr), d3, 0.5);
    TTS_ULP_EQUAL(flx::d4(roundvr), d4, 0.5);
  }

};
