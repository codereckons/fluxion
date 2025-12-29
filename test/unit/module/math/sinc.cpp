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
  TTS_ULP_EQUAL(flx::sinc(data), eve::sinc(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::sinc over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T x)
{
  auto vx1 = flx::variable<4>(x);
  auto ref = flx::rec(vx1)*flx::sin(vx1);
  {
    auto vx = flx::variable<4>(x);
    auto sincvx = flx::sinc(vx);
    TTS_ULP_EQUAL(flx::d0(sincvx), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(sincvx), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(sincvx), flx::d2(ref), 100.0);
    TTS_ULP_EQUAL(flx::d3(sincvx), flx::d3(ref), 400.0);
    TTS_ULP_EQUAL(flx::d4(sincvx), flx::d4(ref), 400.0);
  }
};
