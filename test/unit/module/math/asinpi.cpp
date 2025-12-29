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

TTS_CASE_WITH ( "Check flx::asin over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::asin(data), eve::asin(data));
};

TTS_CASE_WITH ( "Check flx::asin over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto ivp = eve::inv_pi(eve::as(r));
  auto d0 = ivp*eve::asin(r);
  auto d1 = ivp*eve::rsqrt(eve::oneminus(eve::sqr(r)));
  auto d2 = ivp*r*eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 3);
  auto d3 = ivp*(eve::inc(2*eve::sqr(r)))*eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 5);
  auto d4 = ivp*(6*eve::sqr(r)+9)*r* eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 7);
  {
    auto vr = flx::variable<1>(r);
    auto asinpivr = flx::asinpi(vr);
    TTS_ULP_EQUAL(flx::d0(asinpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinpivr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto asinpivr = flx::asinpi(vr);
    TTS_ULP_EQUAL(flx::d0(asinpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinpivr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto asinpivr = flx::asinpi(vr);
    TTS_ULP_EQUAL(flx::d0(asinpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asinpivr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto asinpivr = flx::asinpi(vr);
    TTS_ULP_EQUAL(flx::d0(asinpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asinpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asinpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asinpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(asinpivr), d4, 8.0);
  }
};
