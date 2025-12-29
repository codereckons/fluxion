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

TTS_CASE_WITH ( "Check flx::acsch over real"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::acsch(data), eve::acsch(data), 0.5);
};

TTS_CASE_WITH ( "Check flx::acsch over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto ref = flx::log(flx::sqrt(1+flx::rec(flx::sqr(vr))) +flx::rec(vr));
  auto d0 = flx::d0(ref);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);
  {
    auto vr = flx::variable<1>(r);
    auto acschvr = flx::acsch(vr);
    TTS_ULP_EQUAL(flx::d0(acschvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acschvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto acschvr = flx::acsch(vr);
    TTS_ULP_EQUAL(flx::d0(acschvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acschvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acschvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto acschvr = flx::acsch(vr);
    TTS_ULP_EQUAL(flx::d0(acschvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acschvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acschvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acschvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto acschvr = flx::acsch(vr);
    TTS_ULP_EQUAL(flx::d0(acschvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(acschvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(acschvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(acschvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(acschvr), d4, 10.0);
  }
};
