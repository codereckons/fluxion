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

TTS_CASE_WITH ( "Check flx::acsc over real"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
(auto data)
{
  TTS_EQUAL(flx::acscd(data), eve::acscd(data));
};

TTS_CASE_WITH ( "Check flx::acscd over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
<typename T>(T r)
{
  auto ref = flx::radindeg(flx::acsc(flx::variable<4>(r)));
  {
    auto vr = flx::variable<4>(r);
    auto acscdvr = flx::acscd(vr);
    TTS_ULP_EQUAL(flx::d0(acscdvr), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(acscdvr), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(acscdvr), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(acscdvr), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(acscdvr), flx::d4(ref), 8.0);
  }
};
