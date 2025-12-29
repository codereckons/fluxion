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
    auto fnmavr = flx::fnma(vr, s, t);
    auto fnmavs = flx::fnma( r,vs, t);
    auto fnmavt = flx::fnma(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fnmavr), eve::fnma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmavr), -s, 0.5);
    TTS_ULP_EQUAL(flx::d0(fnmavs), eve::fnma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmavs), -r, 0.5);
    TTS_ULP_EQUAL(flx::d0(fnmavt), eve::fnma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fnmavt), T(1), 0.5);
  }

};
