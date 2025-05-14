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

TTS_CASE_WITH ( "Check flx::acos over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::acos(data), eve::acos(data));
};

TTS_CASE_WITH ( "Check flx::acos over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto d0 = eve::acos(r);
  auto d1 = -eve::rsqrt(eve::oneminus(eve::sqr(r)));
  auto d2 = -r*eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 3);
  auto d3 = -(eve::inc(2*eve::sqr(r)))*eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 5);
  auto d4 = -(6*eve::sqr(r)+9)*r* eve::pow(eve::rsqrt(eve::oneminus(eve::sqr(r))), 7);
  {
    auto vr = flx::variable<1>(r);
    auto acosvr = flx::acos(vr);
    TTS_ULP_EQUAL(flx::D0(acosvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::D1(acosvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acosvr = flx::acos(vr);
    TTS_ULP_EQUAL(flx::D0(acosvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::D1(acosvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::D2(acosvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acosvr = flx::acos(vr);
    TTS_ULP_EQUAL(flx::D0(acosvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::D1(acosvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::D2(acosvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::D3(acosvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acosvr = flx::acos(vr);
    TTS_ULP_EQUAL(flx::D0(acosvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::D1(acosvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::D2(acosvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::D3(acosvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::D4(acosvr), d4, 8.0);
  }
};
