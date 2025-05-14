//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::tan over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,10))
              )
<typename T>(T r)
{
  auto d0 = eve::tan(r);
  auto d1 = eve::inc(eve::sqr(d0));
  auto d2 = d1*2*d0;
  auto sec2 = eve::sqr(eve::sec(r));
  auto d3 = 2*sec2*(2*eve::sqr(d0)+sec2);
  auto d4 = 8*d0*sec2*(eve::sqr(d0)+2*sec2);

  {
    auto vr = flx::variable<1>(r);
    auto tanvr = flx::tan(vr);
    TTS_ULP_EQUAL(flx::D0(tanvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(tanvr), d1, 2.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto tanvr = flx::tan(vr);
    TTS_ULP_EQUAL(flx::D0(tanvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(tanvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(tanvr), d2, 3.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto tanvr = flx::tan(vr);
    TTS_ULP_EQUAL(flx::D0(tanvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(tanvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(tanvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::D3(tanvr), d3, 3.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto tanvr = flx::tan(vr);
    TTS_ULP_EQUAL(flx::D0(tanvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(tanvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(tanvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::D3(tanvr), d3, 3.0);
    TTS_ULP_EQUAL(flx::D4(tanvr), d4, 3.5);
  }

};
