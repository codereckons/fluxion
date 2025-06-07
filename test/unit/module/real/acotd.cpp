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

TTS_CASE_WITH ( "Check flx::acot over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::acot(data), eve::acot(data));
};

TTS_CASE_WITH ( "Check flx::acotd over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto ref = flx::radindeg(flx::acot(flx::variable<4>(r)));
  {
    auto vr = flx::variable<4>(r);
    auto acotdvr = flx::acotd(vr);
    TTS_ULP_EQUAL(flx::d0(acotdvr), flx::d0(ref), 4.0);
    TTS_ULP_EQUAL(flx::d1(acotdvr), flx::d1(ref), 4.0);
    TTS_ULP_EQUAL(flx::d2(acotdvr), flx::d2(ref), 4.0);
    TTS_ULP_EQUAL(flx::d3(acotdvr), flx::d3(ref), 4.0);
    TTS_ULP_EQUAL(flx::d4(acotdvr), flx::d4(ref), 8.0);
  }
};
