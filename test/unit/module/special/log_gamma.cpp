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

TTS_CASE_WITH ( "Check flx::log_gamma over real"
              , flx::real_types
              , tts::generate(tts::randoms(0,5))
              )
(auto data)
{
  TTS_EQUAL(flx::log_gamma(data), eve::log_gamma(data));
};

TTS_CASE_WITH ( "Check flx::log_gamma over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-2, -1))
              )
  <typename T>(T r)
{
  auto d0 = eve::log_gamma(r);
  auto d1 = eve::digamma(r);

  {
    auto vr = flx::variable<1>(r);
    auto log_gammavr = flx::log_gamma(vr);
    TTS_ULP_EQUAL(flx::d0(log_gammavr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(log_gammavr), d1, 4.0);
  }
};
