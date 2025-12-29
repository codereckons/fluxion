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
    auto famvr = flx::fam(vr, s, t);
    auto famvs = flx::fam( r,vs, t);
    auto famvt = flx::fam(r, s, vt);
    TTS_ULP_EQUAL(flx::d0(famvr), eve::fam(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(famvr), T(1), 0.5);
    TTS_ULP_EQUAL(flx::d0(famvs), eve::fam(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(famvs), t, 0.5);
    TTS_ULP_EQUAL(flx::d0(famvt), eve::fam(r, s, t), 0.5);
    TTS_ULP_EQUAL(flx::d1(famvt), s, 0.5);
  }

};
