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

TTS_CASE_WITH ( "Check flx::acos over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::acos(data), eve::acos(data));
};

TTS_CASE_WITH ( "Check flx::acosd over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto ref = flx::radindeg(flx::acos(flx::variable<4>(r)));
  {
    auto vr = flx::variable<4>(r);
    auto acosdvr = flx::acosd(vr);
    TTS_ULP_EQUAL(flx::d0(acosdvr), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(acosdvr), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(acosdvr), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(acosdvr), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(acosdvr), flx::d4(ref), 8.0);
  }
};
