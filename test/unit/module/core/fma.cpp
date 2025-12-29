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
    auto fmavr = flx::fma(vr, s, t);
    auto fmavs = flx::fma( r,vs, t);
    auto fmavt = flx::fma(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(fmavr), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavr), s, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmavs), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavs), r, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmavt), eve::fma(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavt), T(1), 0.5);
  }

};
