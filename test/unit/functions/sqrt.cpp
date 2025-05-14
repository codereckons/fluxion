//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::sqrt over hyperdual 1 to 4"
              , flx::real_types
              , tts::generate(tts::randoms(0,10))
              )
<typename T>(T r)
{
  auto d0 = eve::sqrt(r);
  auto d1 = eve::rec(d0)/2;
  auto d2 = -d1/(2*r);
  auto d3 = -3*d2/(2*r);
  auto d4 = -15/(d0*16*r*r*r);

  {
    auto vr = flx::variable<1>(r);
    auto sqrtvr = flx::sqrt(vr);
    TTS_ULP_EQUAL(flx::D0(sqrtvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(sqrtvr), d1, 2.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto sqrtvr = flx::sqrt(vr);
    TTS_ULP_EQUAL(flx::D0(sqrtvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(sqrtvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(sqrtvr), d2, 2.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto sqrtvr = flx::sqrt(vr);
    TTS_ULP_EQUAL(flx::D0(sqrtvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(sqrtvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(sqrtvr), d2, 2.5);
    TTS_ULP_EQUAL(flx::D3(sqrtvr), d3, 2.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto sqrtvr = flx::sqrt(vr);
    TTS_ULP_EQUAL(flx::D0(sqrtvr), d0, 2.5);
    TTS_ULP_EQUAL(flx::D1(sqrtvr), d1, 2.5);
    TTS_ULP_EQUAL(flx::D2(sqrtvr), d2, 2.5);
    TTS_ULP_EQUAL(flx::D3(sqrtvr), d3, 2.5);
    TTS_ULP_EQUAL(flx::D4(sqrtvr), d4, 2.5);
  }

};
