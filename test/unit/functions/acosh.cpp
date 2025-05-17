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

TTS_CASE_WITH ( "Check flx::acosh over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_EQUAL(flx::acosh(data), eve::acosh(data));
};

TTS_CASE_WITH ( "Check flx::acosh over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
<typename T>(T r)
{
  auto d0   = eve::acosh(r);
  auto rx2m1 = eve::rec(eve::dec(eve::sqr(r)));
  auto d1 = eve::sqrt(rx2m1);
  auto d2 = -r*d1*rx2m1;
  auto d3 = d1*rx2m1*rx2m1*(2*r*r+1);
  auto d4 = -d1*rx2m1*rx2m1*rx2m1*3*r*(2*r*r+3);
  {
    auto vr = flx::variable<1>(r);
    auto acoshvr = flx::acosh(vr);
    TTS_ULP_EQUAL(flx::d0(acoshvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acoshvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acoshvr = flx::acosh(vr);
    TTS_ULP_EQUAL(flx::d0(acoshvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acoshvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acoshvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acoshvr = flx::acosh(vr);
    TTS_ULP_EQUAL(flx::d0(acoshvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acoshvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acoshvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acoshvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acoshvr = flx::acosh(vr);
    TTS_ULP_EQUAL(flx::d0(acoshvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acoshvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acoshvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acoshvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(acoshvr), d4, 8.0);
  }
};
