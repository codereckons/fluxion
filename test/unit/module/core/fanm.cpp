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
    auto fanmvr = flx::fanm(vr, s, t);
    auto fanmvs = flx::fanm( r,vs, t);
    auto fanmvt = flx::fanm(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fanmvr), eve::fanm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fanmvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d0(fanmvs), eve::fanm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fanmvs), -t, 0.5);
    TTS_ULP_EQUAL(flx::d0(fanmvt), eve::fanm(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fanmvt), -s, 0.5);
  }

};
