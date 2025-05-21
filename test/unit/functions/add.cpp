//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::add over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{

  {
    auto vr = flx::variable<1>(r);
    auto addvr = flx::add(vr, s);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto addvr = flx::add(vr, s);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto addvr = flx::add(vr, s);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(addvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto addvr = flx::add(vr, s);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(addvr), T(0), 0.5);
  }


  {
    auto vr = flx::variable<1>(r);
    auto addvr = flx::add(s, vr);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto addvr = flx::add(s, vr);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto addvr = flx::add(s, vr);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(addvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto addvr = flx::add(s, vr);
    TTS_ULP_EQUAL(flx::d0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::d1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(addvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(addvr), T(0), 0.5);
  }
  {
    auto [a, b] = flx::variable2<0, 1, 1>(r, s);
    auto addvr = flx::add(a, b);
    TTS_ULP_EQUAL(flx::e0(addvr), r+s, 0.5);
    TTS_ULP_EQUAL(flx::e1(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::e2(addvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::e12(addvr),T(0), 0.5);
  }
};
