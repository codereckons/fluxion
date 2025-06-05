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

TTS_CASE_WITH ( "Check flx::sec over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::sec(data), eve::sec(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::sec over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T x)
{
//  auto vx = flx::variable<4>(x);
//  auto ref = flx::rec(flx::cos(vx));
  auto d0 =  eve::sec(x);
  auto d1 =  eve::tan(x)*eve::sec(x);
  auto d2 =  eve::sec(x)*(eve::sqr(eve::tan(x)) + eve::sqr(eve::sec(x)));
  auto d3 =  eve::tan(x)*eve::sec(x)*(eve::sqr(eve::tan(x)) + 5*eve::sqr(eve::sec(x)));
  auto d4 =  eve::sec(x)*(eve::sqr(eve::sqr(eve::tan(x))) + 5*eve::sqr(eve::sqr(eve::sec(x))) + 18*eve::sqr(eve::tan(x)*eve::sec(x)));
  {
    auto vx = flx::variable<4>(x);
    auto secvx = flx::sec(vx);
    TTS_ULP_EQUAL(flx::d0(secvx), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(secvx), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(secvx), d2, 100.0);
    TTS_ULP_EQUAL(flx::d3(secvx), d3, 400.0);
    TTS_ULP_EQUAL(flx::d4(secvx), d4, 400.0);
  }
};
