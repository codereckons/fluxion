//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::secd over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(1,80))
              )
  <typename T>(T r)
{
  auto vr = flx::variable<4>(eve::deginrad(r));
  T deg(1.745329251994330e-02);
  auto secvr = flx::sec(vr);
  auto d0 = flx::d0(secvr);
  auto d1 = flx::d1(secvr)*deg;
  auto d2 = flx::d2(secvr)*deg*deg;
  auto d3 = flx::d3(secvr)*deg*deg*deg;
  auto d4 = flx::d4(secvr)*deg*deg*deg*deg;
  auto vd = flx::variable<4>(r);
  auto secdvd = flx::secd(vd);
  TTS_ULP_EQUAL(flx::d0(secdvd), d0, 20.0);
  TTS_ULP_EQUAL(flx::d1(secdvd), d1, 20.0);
  TTS_ULP_EQUAL(flx::d2(secdvd), d2, 20.0);
  TTS_ULP_EQUAL(flx::d3(secdvd), d3, 20.0);
  TTS_ULP_EQUAL(flx::d4(secdvd), d4, 23.0);
};
