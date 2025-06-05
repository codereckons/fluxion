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

TTS_CASE_WITH ( "Check flx::floor over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_EQUAL(flx::floor(data), eve::floor(data));
};

TTS_CASE_WITH ( "Check flx::floor over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r)
{
  auto d0   = eve::floor(r);
  auto d1 = T(0);
  auto d2 = T(0);
  auto d3 = T(0);
  auto d4 = T(0);
  {
    auto vr = flx::variable<4>(r);
    auto floorvr = flx::floor(vr);
    TTS_ULP_EQUAL(flx::d0(floorvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(floorvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(floorvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(floorvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(floorvr), d4, 8.0);
  }
};
