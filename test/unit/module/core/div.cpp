//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::div over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{

  {
    auto vr = flx::variable<1>(r);
    auto divvr = flx::div(vr, s);
    TTS_ULP_EQUAL(flx::d0(divvr), r/s, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), T(1)/s, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto divvr = flx::div(vr, s);
    TTS_ULP_EQUAL(flx::d0(divvr), r/s, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), T(1)/s, 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto divvr = flx::div(vr, s);
    TTS_ULP_EQUAL(flx::d0(divvr), r/s, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), T(1)/s, 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(divvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto divvr = flx::div(vr, s);
    TTS_ULP_EQUAL(flx::d0(divvr), r/s, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), T(1)/s, 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(divvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(divvr), T(0), 0.5);
  }


  {
    auto vr = flx::variable<1>(r);
    auto divvr = flx::div(s, vr);
    auto ref = s*flx::rec(vr);
    TTS_ULP_EQUAL(flx::d0(divvr), s/r, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), flx::d1(ref), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto divvr = flx::div(s, vr);
    auto ref = s*flx::rec(vr);
    TTS_ULP_EQUAL(flx::d0(divvr), s/r, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), flx::d1(ref), 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), flx::d2(ref), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto divvr = flx::div(s, vr);
    auto ref = s*flx::rec(vr);
    TTS_ULP_EQUAL(flx::d0(divvr), s/r, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), flx::d1(ref), 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), flx::d2(ref), 0.5);
    TTS_ULP_EQUAL(flx::d3(divvr), flx::d3(ref), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto divvr = flx::div(s, vr);
    auto ref = s*flx::rec(vr);
    TTS_ULP_EQUAL(flx::d0(divvr), s/r, 0.5);
    TTS_ULP_EQUAL(flx::d1(divvr), flx::d1(ref), 0.5);
    TTS_ULP_EQUAL(flx::d2(divvr), flx::d2(ref), 0.5);
    TTS_ULP_EQUAL(flx::d3(divvr), flx::d3(ref), 0.5);
    TTS_ULP_EQUAL(flx::d4(divvr), flx::d4(ref), 0.5);
  }

  {
    auto [a, b] = flx::variable2<0, 1>(r, s);
    auto divvr = flx::div(a, b);
    TTS_ULP_EQUAL(flx::e0(divvr), r/s, 0.5);
    TTS_ULP_EQUAL(flx::e1(divvr), eve::rec(s), 0.5);
    TTS_ULP_EQUAL(flx::e2(divvr), -r/(s*s), 2.5);
    TTS_ULP_EQUAL(flx::e12(divvr), -eve::rec(s*s), 2.5);
  }
};
