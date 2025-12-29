//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::cotd over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(1,80))
              )
  <typename T>(T r)
{
  auto vr = flx::variable<4>(eve::deginrad(r));
  T deg(1.745329251994330e-02);
  auto cotvr = flx::cot(vr);
  auto d0 = flx::d0(cotvr);
  auto d1 = flx::d1(cotvr)*deg;
  auto d2 = flx::d2(cotvr)*deg*deg;
  auto d3 = flx::d3(cotvr)*deg*deg*deg;
  auto d4 = flx::d4(cotvr)*deg*deg*deg*deg;
  auto vd = flx::variable<4>(r);
  auto cotdvd = flx::cotd(vd);
  TTS_ULP_EQUAL(flx::d0(cotdvd), d0, 20.0);
  TTS_ULP_EQUAL(flx::d1(cotdvd), d1, 20.0);
  TTS_ULP_EQUAL(flx::d2(cotdvd), d2, 20.0);
  TTS_ULP_EQUAL(flx::d3(cotdvd), d3, 20.0);
  TTS_ULP_EQUAL(flx::d4(cotdvd), d4, 20.0);
};
