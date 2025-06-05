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

TTS_CASE_WITH ( "Check flx::asec over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_EQUAL(flx::asec(data), eve::asec(data));
};

TTS_CASE_WITH ( "Check flx::asec over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
<typename T>(T r)
{
  auto d0 = eve::asec(r);
  auto d1 = eve::rec(eve::sqrt(1-eve::rec(r*r))*r*r);
  auto d2 = -(2*r*r-1)/(eve::sqrt(1-eve::rec(r*r))*r*r*r*(r*r-1));
  auto d3 = -(-6*r*r*r*r+5*r*r-2)/(eve::sqrt(1-eve::rec(r*r))*r*r*r*r*eve::sqr(r*r-1));
  auto d4 = -3*(8*r*r*r*r*r*r-8*r*r*r*r+7*r*r-2)/(eve::sqrt(1-eve::rec(r*r))*r*r*r*r*r*eve::pow(r*r-1, 3));
  {
    auto vr = flx::variable<1>(r);
    auto asecvr = flx::asec(vr);
    TTS_ULP_EQUAL(flx::d0(asecvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asecvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto asecvr = flx::asec(vr);
    TTS_ULP_EQUAL(flx::d0(asecvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asecvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asecvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto asecvr = flx::asec(vr);
    TTS_ULP_EQUAL(flx::d0(asecvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asecvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asecvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asecvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto asecvr = flx::asec(vr);
    TTS_ULP_EQUAL(flx::d0(asecvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asecvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asecvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asecvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(asecvr), d4, 8.0);
  }
};
