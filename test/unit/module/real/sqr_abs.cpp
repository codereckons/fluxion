//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sqr_abs over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
(auto data)
{
  TTS_EQUAL(flx::sqr_abs(data), eve::sqr(data));
};

TTS_CASE_WITH ( "Check flx::sqr_abs over dual"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T x)
{
  auto vx1 = flx::variable<4>(x);
  auto ref = flx::sqr(vx1);
  {
    auto vx = flx::variable<4>(x);
    auto sqr_absvx = flx::sqr_abs(vx);
    TTS_ULP_EQUAL(flx::d0(sqr_absvx), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(sqr_absvx), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(sqr_absvx), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(sqr_absvx), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(sqr_absvx), flx::d4(ref), 4.0);
  }
};
