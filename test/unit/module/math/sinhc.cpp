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

TTS_CASE_WITH ( "Check flx::sinc over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::sinhc(data), eve::sinhc(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::sinc over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T x)
{
  auto vx1 = flx::variable<4>(x);
  auto ref = flx::rec(vx1)*flx::sinh(vx1);
  {
    auto vx = flx::variable<4>(x);
    auto sinhcvx = flx::sinhc(vx);
    TTS_ULP_EQUAL(flx::d0(sinhcvx), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(sinhcvx), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(sinhcvx), flx::d2(ref), 100.0);
    TTS_ULP_EQUAL(flx::d3(sinhcvx), flx::d3(ref), 400.0);
    TTS_ULP_EQUAL(flx::d4(sinhcvx), flx::d4(ref), 400.0);
  }
};
