//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::acoth over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(1,5))
              )
<typename T>(T r)
{
  auto x2m1 = eve::rec(eve::oneminus(eve::sqr(r)));
  auto d0 = eve::acoth(r);
  auto d1 = x2m1;
  auto d2 = 2*r*eve::sqr(x2m1);
  auto d3 = eve::sqr(x2m1)*x2m1*(2+6*r*r);
  auto d4 = 24*r*(r*r+1)*eve::sqr(eve::sqr(x2m1));

  TTS_EQUAL(flx::acoth(r), d0);
  {
    auto vr = flx::variable<1>(r);
    auto acothvr = flx::acoth(vr);
    TTS_ULP_EQUAL(flx::d0(acothvr), d0, 20.0);
    TTS_ULP_EQUAL(flx::d1(acothvr), d1, 20.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acothvr = flx::acoth(vr);
    TTS_ULP_EQUAL(flx::d0(acothvr), d0, 20.0);
    TTS_ULP_EQUAL(flx::d1(acothvr), d1, 20.0);
    TTS_ULP_EQUAL(flx::d2(acothvr), d2, 20.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acothvr = flx::acoth(vr);
    TTS_ULP_EQUAL(flx::d0(acothvr), d0, 20.0);
    TTS_ULP_EQUAL(flx::d1(acothvr), d1, 20.0);
    TTS_ULP_EQUAL(flx::d2(acothvr), d2, 20.0);
    TTS_ULP_EQUAL(flx::d3(acothvr), d3, 20.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acothvr = flx::acoth(vr);
    TTS_ULP_EQUAL(flx::d0(acothvr), d0, 20.0);
    TTS_ULP_EQUAL(flx::d1(acothvr), d1, 20.0);
    TTS_ULP_EQUAL(flx::d2(acothvr), d2, 20.0);
    TTS_ULP_EQUAL(flx::d3(acothvr), d3, 20.0);
    TTS_ULP_EQUAL(flx::d4(acothvr), d4, 20.0);
  }
};
