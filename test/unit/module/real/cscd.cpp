//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::cscd over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(1,80))
              )
  <typename T>(T r)
{
  auto vr = flx::variable<4>(eve::deginrad(r));
  T deg(1.745329251994330e-02);
  auto cscvr = flx::csc(vr);
  auto d0 = flx::d0(cscvr);
  auto d1 = flx::d1(cscvr)*deg;
  auto d2 = flx::d2(cscvr)*deg*deg;
  auto d3 = flx::d3(cscvr)*deg*deg*deg;
  auto d4 = flx::d4(cscvr)*deg*deg*deg*deg;
  auto vd = flx::variable<4>(r);
  auto cscdvd = flx::cscd(vd);
  TTS_ULP_EQUAL(flx::d0(cscdvd), d0, 20.0);
  TTS_ULP_EQUAL(flx::d1(cscdvd), d1, 20.0);
  TTS_ULP_EQUAL(flx::d2(cscdvd), d2, 20.0);
  TTS_ULP_EQUAL(flx::d3(cscdvd), d3, 20.0);
  TTS_ULP_EQUAL(flx::d4(cscdvd), d4, 20.0);
};
