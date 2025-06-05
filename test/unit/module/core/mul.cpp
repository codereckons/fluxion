//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::mul over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{

  {
    auto vr = flx::variable<1>(r);
    auto mulvr = flx::mul(vr, s);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto mulvr = flx::mul(vr, s);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto mulvr = flx::mul(vr, s);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(mulvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto mulvr = flx::mul(vr, s);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(mulvr), T(0), 0.5);
  }


  {
    auto vr = flx::variable<1>(r);
    auto mulvr = flx::mul(s, vr);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto mulvr = flx::mul(s, vr);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto mulvr = flx::mul(s, vr);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(mulvr), T(0), 0.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto mulvr = flx::mul(s, vr);
    TTS_ULP_EQUAL(flx::d0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::d1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d2(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(mulvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(mulvr), T(0), 0.5);
  }

  {
    auto [a, b] = flx::variable2<0, 1>(r, s);
    auto mulvr = flx::mul(a, b);
    TTS_ULP_EQUAL(flx::e0(mulvr), r*s, 0.5);
    TTS_ULP_EQUAL(flx::e1(mulvr), s, 0.5);
    TTS_ULP_EQUAL(flx::e2(mulvr), r   , 0.5);
    TTS_ULP_EQUAL(flx::e12(mulvr), T(1), 0.5);
  }
};
