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
  auto d0 = s;
  auto d1 = c*pi;
  auto d2 = -s*pi*pi;
  auto d3 = -c*pi*pi*pi;
  auto d4 = s*pi*pi*pi*pi;
  {
    auto vr = flx::variable<1>(r);
    auto sinpivr = flx::sinpi(vr);
    TTS_ULP_EQUAL(flx::d0(sinpivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(sinpivr), d1, 1.5);
  }
  {
    auto vr = flx::variable<2>(r);
    auto sinpivr = flx::sinpi(vr);
    TTS_ULP_EQUAL(flx::d0(sinpivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(sinpivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(sinpivr), d2, 1.5);
  }
  {
    auto vr = flx::variable<3>(r);
    auto sinpivr = flx::sinpi(vr);
    TTS_ULP_EQUAL(flx::d0(sinpivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(sinpivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(sinpivr), d2, 1.5);
    TTS_ULP_EQUAL(flx::d3(sinpivr), d3, 1.5);
  }
  {
    auto vr = flx::variable<4>(r);
    auto sinpivr = flx::sinpi(vr);
    TTS_ULP_EQUAL(flx::d0(sinpivr), d0, 1.5);
    TTS_ULP_EQUAL(flx::d1(sinpivr), d1, 1.5);
    TTS_ULP_EQUAL(flx::d2(sinpivr), d2, 1.5);
    TTS_ULP_EQUAL(flx::d3(sinpivr), d3, 1.5);
    TTS_ULP_EQUAL(flx::d4(sinpivr), d4, 1.5);
  }
};
