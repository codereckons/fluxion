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

TTS_CASE_WITH ( "Check flx::asec over real"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
(auto data)
{
  TTS_EQUAL(flx::asec(data), eve::asec(data));
};

TTS_CASE_WITH ( "Check flx::asecd over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1, 10))
              )
<typename T>(T r)
{
  auto ref = flx::radindeg(flx::asec(flx::variable<4>(r)));
  {
    auto vr = flx::variable<4>(r);
    auto asecdvr = flx::asecd(vr);
    TTS_ULP_EQUAL(flx::d0(asecdvr), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(asecdvr), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(asecdvr), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(asecdvr), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(asecdvr), flx::d4(ref), 8.0);
  }
};
