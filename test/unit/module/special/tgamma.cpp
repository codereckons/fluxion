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

TTS_CASE_WITH ( "Check flx::tgamma over real"
              , flx::real_types
              , tts::generate(tts::randoms(-1,1))
              )
(auto data)
{
  TTS_EQUAL(flx::tgamma(data), eve::tgamma(data));
};

TTS_CASE_WITH ( "Check flx::tgamma over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1))
              )
<typename T>(T r)
{
  auto d0 = eve::tgamma(r);
  auto d1 = eve::digamma(r)*d0;

  {
    auto vr = flx::variable<1>(r);
    auto tgammavr = flx::tgamma(vr);
    TTS_ULP_EQUAL(flx::d0(tgammavr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(tgammavr), d1, 4.0);
  }
};
