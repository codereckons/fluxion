//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::average over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{

  {
    auto vr = flx::variable<1>(r);
    auto averagevr = flx::average(vr, s);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto averagevr = flx::average(vr, s);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto averagevr = flx::average(vr, s);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(averagevr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto averagevr = flx::average(vr, s);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(averagevr), T(0), 0.5);
  }


  {
    auto vr = flx::variable<1>(r);
    auto averagevr = flx::average(s, vr);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto averagevr = flx::average(s, vr);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto averagevr = flx::average(s, vr);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(averagevr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto averagevr = flx::average(s, vr);
    TTS_ULP_EQUAL(flx::d0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::d1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::d2(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(averagevr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(averagevr), T(0), 0.5);
  }

  {
    auto [a, b] = flx::variable2<0, 1, 1>(r, s);
    auto averagevr = flx::average(a, b);
    TTS_ULP_EQUAL(flx::e0(averagevr), (r+s)/2, 0.5);
    TTS_ULP_EQUAL(flx::e1(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::e2(averagevr), T(0.5), 0.5);
    TTS_ULP_EQUAL(flx::e12(averagevr),T(0.0), 0.5);
  }
};
