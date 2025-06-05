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

TTS_CASE_WITH ( "Check flx::cscpi over real"
              , flx::real_types
              , tts::generate(tts::randoms(-10, 10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::cscpi(data), eve::cscpi(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::cscpi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10, 10))
              )
<typename T>(T r)
{
  auto pi = eve::pi(eve::as(r));
  auto vr = flx::variable<4>(r);
  auto ref = flx::csc(pi*vr);
  auto d0 = eve::cscpi(r);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);

   {
    auto vr = flx::variable<4>(r);
    auto cscpivr = flx::cscpi(vr);
    TTS_ULP_EQUAL(flx::d0(cscpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cscpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(cscpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(cscpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(cscpivr), d4, 8.0);
  }
};
