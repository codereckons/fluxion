//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::fsnm over hyperduals"
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
    auto fsnmvr = flx::fsnm(vr, s, t);
    auto fsnmvs = flx::fsnm( r,vs, t);
    auto fsnmvt = flx::fsnm(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fsnmvr), eve::fsnm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsnmvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::d0(fsnmvs), eve::fsnm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsnmvs), -t, 0.5);
    TTS_ULP_EQUAL(flx::d0(fsnmvt), eve::fsnm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsnmvt), -s, 0.5);
  }

};
