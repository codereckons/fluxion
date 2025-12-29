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

TTS_CASE_WITH ( "Check flx::asech over real"
              , flx::real_types
              , tts::generate(tts::randoms(1, 5))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::asech(data), eve::asech(data), 0.5);
};

TTS_CASE_WITH ( "Check flx::asech over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(1, 5))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto ref = flx::log(flx::sqrt(1+flx::rec(vr))*flx::sqrt(flx::rec(vr)-1) +flx::rec(vr));
  auto d0 = flx::d0(ref);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);
  {
    auto vr = flx::variable<1>(r);
    auto asechvr = flx::asech(vr);
    TTS_ULP_EQUAL(flx::d0(asechvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asechvr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto asechvr = flx::asech(vr);
    TTS_ULP_EQUAL(flx::d0(asechvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asechvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asechvr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto asechvr = flx::asech(vr);
    TTS_ULP_EQUAL(flx::d0(asechvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asechvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asechvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asechvr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto asechvr = flx::asech(vr);
    TTS_ULP_EQUAL(flx::d0(asechvr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(asechvr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(asechvr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(asechvr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(asechvr), d4, 8.0);
  }
};
