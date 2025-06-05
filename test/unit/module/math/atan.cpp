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

TTS_CASE_WITH ( "Check flx::atan over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::atan(data), eve::atan(data));
};

TTS_CASE_WITH ( "Check flx::atan over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto d0 = eve::atan(r);
  auto d1 = eve::rec(eve::inc(eve::sqr(r)));
  auto d2 = -2*r*eve::pow(d1, 2);
  auto d3 = 6*eve::sqr(r)*eve::sqr(d1*d1)*d1;
  auto d4 =  24*r*(eve::dec(eve::sqr(r)))*eve::sqr(eve::sqr(d1));
  {
    auto vr = flx::variable<1>(r);
    auto atanvr = flx::atan(vr);
    TTS_ULP_EQUAL(flx::d0(atanvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto atanvr = flx::atan(vr);
    TTS_ULP_EQUAL(flx::d0(atanvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto atanvr = flx::atan(vr);
    TTS_ULP_EQUAL(flx::d0(atanvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto atanvr = flx::atan(vr);
    TTS_ULP_EQUAL(flx::d0(atanvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(atanvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(atanvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(atanvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(atanvr), d4, 8.0);
  }
};
