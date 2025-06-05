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
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{

  {
    auto vr = flx::variable<3>(r);
    auto hornervr = flx::horner(vr, T(1.0), T(2.0), T(3.0));
    TTS_ULP_EQUAL(flx::d0(hornervr), eve::horner(r,T(1.0), T(2.0), T(3.0)) , 0.5);
    TTS_ULP_EQUAL(flx::d1(hornervr), eve::horner(r,T(2.0), T(2.0)), 0.5);
    TTS_ULP_EQUAL(flx::d2(hornervr), eve::horner(r,T(2.0)), 0.5);
    TTS_ULP_EQUAL(flx::d3(hornervr), T(0.0), 0.5);
  }

};
