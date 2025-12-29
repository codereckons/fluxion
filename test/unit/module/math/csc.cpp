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

TTS_CASE_WITH ( "Check flx::csc over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::csc(data), eve::csc(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::csc over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T x)
{
//  auto vx = flx::variable<4>(x);
//  auto ref = flx::rec(flx::sin(vx));
  auto d0 = eve::csc(x);
  auto d1 = -eve::cot(x)*eve::csc(x);
  auto d2 =  eve::csc(x)*(eve::sqr(eve::cot(x)) + eve::sqr(eve::csc(x)));
  auto d3 = -eve::cot(x)*eve::csc(x)*(eve::sqr(eve::cot(x)) + 5*eve::sqr(eve::csc(x)));
  auto d4 =  eve::csc(x)*(eve::sqr(eve::sqr(eve::cot(x))) + 5*eve::sqr(eve::sqr(eve::csc(x))) + 18*eve::sqr(eve::cot(x)*eve::csc(x)));
  {
    auto vx = flx::variable<4>(x);
    auto cscvx = flx::csc(vx);
    TTS_ULP_EQUAL(flx::d0(cscvx), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cscvx), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(cscvx), d2, 100.0);
    TTS_ULP_EQUAL(flx::d3(cscvx), d3, 400.0);
    TTS_ULP_EQUAL(flx::d4(cscvx), d4, 400.0);
  }
};
