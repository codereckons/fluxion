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
    auto fnmsvr = flx::fnms(vr, s, t);
    auto fnmsvs = flx::fnms( r,vs, t);
    auto fnmsvt = flx::fnms(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fnmsvr), eve::fnms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmsvr), -s, 0.5);
    TTS_ULP_EQUAL(flx::d0(fnmsvs), eve::fnms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmsvs), -r, 0.5);
    TTS_ULP_EQUAL(flx::d0(fnmsvt), eve::fnms(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmsvt), T(-1), 0.5);
  }

};
