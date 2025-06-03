//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_WITH ( "Check flx::secpi over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10, 10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::secpi(data), eve::secpi(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::secpi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10, 10))
              )
<typename T>(T r)
{
  auto pi = eve::pi(eve::as(r));
  auto vr = flx::variable<4>(r);
  auto ref = flx::sec(pi*vr);
  auto d0 = eve::secpi(r);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);

   {
    auto vr = flx::variable<4>(r);
    auto secpivr = flx::secpi(vr);
    TTS_ULP_EQUAL(flx::d0(secpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(secpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(secpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(secpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(secpivr), d4, 8.0);
  }
};
