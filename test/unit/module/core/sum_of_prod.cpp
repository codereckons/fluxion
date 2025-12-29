//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::sum_of_prod over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s,  T t,  T u)
{

  {
    auto vr = flx::variable<1>(r);
    auto vs = flx::variable<1>(s);
    auto vt = flx::variable<1>(t);
    auto vu = flx::variable<1>(u);
    auto fmavr = flx::sum_of_prod(vr, s, t, u);
    auto fmavs = flx::sum_of_prod(r, vs, t, u);
    auto fmavt = flx::sum_of_prod(r, s, vt, u);
    auto fmavu = flx::sum_of_prod(r, s,  t, vu);
    TTS_ULP_EQUAL(flx::d0(fmavr), eve::sum_of_prod(r, s, t, u), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavr), s, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmavs), eve::sum_of_prod(r, s, t, u), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavs), r, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmavt), eve::sum_of_prod(r, s, t, u), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavt), u, 0.5);
    TTS_ULP_EQUAL(flx::d0(fmavu), eve::sum_of_prod(r, s, t, u), 0.5);
    TTS_ULP_EQUAL(flx::d1(fmavu), t, 0.5);
  }

};
