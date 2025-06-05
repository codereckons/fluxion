//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check flx::sinpi over hyperdual 4"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto [sinpivr, cospivr] = flx::sinpicospi(vr);
  auto [s, c] = eve::sinpicospi(r);
  auto pi = eve::pi(eve::as(r));
  TTS_ULP_EQUAL(flx::d0(sinpivr),  s, 1.5);
  TTS_ULP_EQUAL(flx::d1(sinpivr),  c*pi, 1.5);
  TTS_ULP_EQUAL(flx::d2(sinpivr), -s*pi*pi, 1.5);
  TTS_ULP_EQUAL(flx::d3(sinpivr), -c*pi*pi*pi, 1.5);
  TTS_ULP_EQUAL(flx::d4(sinpivr),  s*pi*pi*pi*pi, 1.5);
  TTS_ULP_EQUAL(flx::d0(cospivr),  c, 1.5);
  TTS_ULP_EQUAL(flx::d1(cospivr), -s*pi, 1.5);
  TTS_ULP_EQUAL(flx::d2(cospivr), -c*pi*pi, 1.5);
  TTS_ULP_EQUAL(flx::d3(cospivr),  s*pi*pi*pi, 1.5);
  TTS_ULP_EQUAL(flx::d4(cospivr),  c*pi*pi*pi*pi, 1.5);
};
