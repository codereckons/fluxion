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
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s,  T t)
{

  {
    auto vr = flx::variable<1>(r);
    auto vs = flx::variable<1>(s);
    auto vt = flx::variable<1>(t);
    auto fmsvr = flx::fms(vr, s, t);
    auto fmsvs = flx::fms( r,vs, t);
    auto fmsvt = flx::fms(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fmsvr), eve::fms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmsvr), s, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmsvs), eve::fms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmsvs), r, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmsvt), eve::fms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmsvt), T(-1), 0.5);
  }

};
