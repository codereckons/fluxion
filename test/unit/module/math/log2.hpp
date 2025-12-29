//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::log2 over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,2))
              )
<typename T>(T r)
{
  auto il10 = eve::invlog_10(eve::as(r));
  auto d0 = eve::log2(r);
  auto rr = eve::rec(r);
  auto d1 = rr*il10;
  auto d2 = -rr*rr*il10;
  auto d3 = -2*d2*rr;
  auto d4 = -3*d3*rr;

  TTS_EQUAL(flx::log2(r), d0);
  {
    auto vr = flx::variable<1>(r);
    auto log2vr = flx::log2(vr);
    TTS_ULP_EQUAL(flx::d0(log2vr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(log2vr), d1, 2.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto log2vr = flx::log2(vr);
    TTS_ULP_EQUAL(flx::d0(log2vr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(log2vr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(log2vr), d2, 3.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto log2vr = flx::log2(vr);
    TTS_ULP_EQUAL(flx::d0(log2vr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(log2vr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(log2vr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(log2vr), d3, 3.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto log2vr = flx::log2(vr);
    TTS_ULP_EQUAL(flx::d0(log2vr), d0, 2.5);
    TTS_ULP_EQUAL(flx::d1(log2vr), d1, 2.5);
    TTS_ULP_EQUAL(flx::d2(log2vr), d2, 3.0);
    TTS_ULP_EQUAL(flx::d3(log2vr), d3, 3.0);
    TTS_ULP_EQUAL(flx::d4(log2vr), d4, 3.5);
  }
};
