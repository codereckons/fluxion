//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::fsm over hyperduals"
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
    auto fsmvr = flx::fsm(vr, s, t);
    auto fsmvs = flx::fsm( r,vs, t);
    auto fsmvt = flx::fsm(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fsmvr), eve::fsm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsmvr), T(-1), 0.5);
    TTS_ULP_EQUAL(flx::d0(fsmvs), eve::fsm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsmvs), t, 0.5);
    TTS_ULP_EQUAL(flx::d0(fsmvt), eve::fsm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fsmvt), s, 0.5);
  }

};
