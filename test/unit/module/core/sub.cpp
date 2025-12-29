//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sub over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{

  {
    auto vr = flx::variable<1>(r);
    auto subvr = flx::sub(vr, s);
    TTS_ULP_EQUAL(flx::d0(subvr), r-s, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(1), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto subvr = flx::sub(vr, s);
    TTS_ULP_EQUAL(flx::d0(subvr), r-s, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto subvr = flx::sub(vr, s);
    TTS_ULP_EQUAL(flx::d0(subvr), r-s, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(subvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto subvr = flx::sub(vr, s);
    TTS_ULP_EQUAL(flx::d0(subvr), r-s, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(subvr), T(0), 0.5);
  }


  {
    auto vr = flx::variable<1>(r);
    auto subvr = flx::sub(s, vr);
    TTS_ULP_EQUAL(flx::d0(subvr), s-r, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(-1), 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto subvr = flx::sub(s, vr);
    TTS_ULP_EQUAL(flx::d0(subvr), s-r, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto subvr = flx::sub(s, vr);
    TTS_ULP_EQUAL(flx::d0(subvr), s-r, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(subvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto subvr = flx::sub(s, vr);
    TTS_ULP_EQUAL(flx::d0(subvr), s-r, 0.5);
    TTS_ULP_EQUAL(flx::d1(subvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::d2(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(subvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(subvr), T(0), 0.5);
  }
  {
    auto [a, b] = flx::variable2<0, 1>(r, s);
    auto subvr = flx::sub(a, b);
    TTS_ULP_EQUAL(flx::e0(subvr), r-s, 0.5);
    TTS_ULP_EQUAL(flx::e1(subvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::e2(subvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::e12(subvr),T(0), 0.5);
  }
};
