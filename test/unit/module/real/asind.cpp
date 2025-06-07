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

TTS_CASE_WITH ( "Check flx::asin over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::asin(data), eve::asin(data));
};

TTS_CASE_WITH ( "Check flx::asind over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto ref = flx::radindeg(flx::asin(flx::variable<4>(r)));
  {
    auto vr = flx::variable<4>(r);
    auto asindvr = flx::asind(vr);
    TTS_ULP_EQUAL(flx::d0(asindvr), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(asindvr), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(asindvr), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(asindvr), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(asindvr), flx::d4(ref), 8.0);
  }
};
