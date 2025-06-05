//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::acot over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,2))
              )
<typename T>(T r)
{
  auto x2p1 = eve::rec(eve::inc(eve::sqr(r)));
  auto d0 = eve::acot(r);
  auto d1 = -x2p1;
  auto d2 = 2*r*eve::sqr(x2p1);
  auto d3 = eve::sqr(x2p1)*x2p1*(2-6*r*r);
  auto d4 = 24*r*(r*r-1)*eve::sqr(eve::sqr(x2p1));

  TTS_EQUAL(flx::acot(r), d0);
  {
    auto vr = flx::variable<1>(r);
    auto acotvr = flx::acot(vr);
    TTS_ULP_EQUAL(flx::d0(acotvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(acotvr), d1, 2.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acotvr = flx::acot(vr);
    TTS_ULP_EQUAL(flx::d0(acotvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(acotvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(acotvr), d2, 3.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acotvr = flx::acot(vr);
    TTS_ULP_EQUAL(flx::d0(acotvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(acotvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(acotvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(acotvr), d3, 3.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acotvr = flx::acot(vr);
    TTS_ULP_EQUAL(flx::d0(acotvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(acotvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(acotvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(acotvr), d3, 3.0);
    TTS_ULP_EQUAL(flx::d4(acotvr), d4, 3.5);
  }
};
