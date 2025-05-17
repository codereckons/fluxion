//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::log over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,2))
              )
<typename T>(T r)
{
  auto d0 = eve::log(r);
  auto rr = eve::rec(r);
  auto d1 = rr;
  auto d2 = -rr*rr;
  auto d3 = -2*d2*rr;
  auto d4 = -3*d3*rr;

  TTS_EQUAL(flx::log(r), d0);
  {
    auto vr = flx::variable<1>(r);
    auto logvr = flx::log(vr);
    TTS_ULP_EQUAL(flx::d0(logvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(logvr), d1, 2.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto logvr = flx::log(vr);
    TTS_ULP_EQUAL(flx::d0(logvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(logvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(logvr), d2, 3.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto logvr = flx::log(vr);
    TTS_ULP_EQUAL(flx::d0(logvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(logvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(logvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(logvr), d3, 3.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto logvr = flx::log(vr);
    TTS_ULP_EQUAL(flx::d0(logvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(logvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(logvr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(logvr), d3, 3.0);
    TTS_ULP_EQUAL(flx::d4(logvr), d4, 3.5);
  }
};
