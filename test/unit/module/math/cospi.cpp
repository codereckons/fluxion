//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::cos over hyperdual 3"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T r)
{
  auto [s, c] = eve::sinpicospi(r);
  auto pi = eve::pi(eve::as(r));
  auto d0 = c;
  auto d1 = -s*pi;
  auto d2 = -c*pi*pi;
  auto d3 = s*pi*pi*pi;
  auto d4 = c*pi*pi*pi*pi;
  {
    auto vr = flx::variable<1>(r);
    auto cospivr = flx::cospi(vr);
    TTS_ULP_EQUAL(flx::d0(cospivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(cospivr), d1, 1.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto cospivr = flx::cospi(vr);
    TTS_ULP_EQUAL(flx::d0(cospivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(cospivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(cospivr), d2, 1.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto cospivr = flx::cospi(vr);
    TTS_ULP_EQUAL(flx::d0(cospivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(cospivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(cospivr), d2, 1.5);
    TTS_ULP_EQUAL(flx::d3(cospivr), d3, 1.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto cospivr = flx::cospi(vr);
    TTS_ULP_EQUAL(flx::d0(cospivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(cospivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(cospivr), d2, 1.5);
    TTS_ULP_EQUAL(flx::d3(cospivr), d3, 1.5);
    TTS_ULP_EQUAL(flx::d4(cospivr), d4, 1.5);
  }
};
