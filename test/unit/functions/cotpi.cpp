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

TTS_CASE_WITH ( "Check flx::cotpi over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::cotpi(data), eve::cotpi(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::cotpi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T r)
{
  auto pi = eve::pi(eve::as(r));
  auto vr = flx::variable<4>(r);
  auto ref = flx::cot(pi*vr);
  auto d0 = eve::cotpi(r);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);
  {
    auto vr = flx::variable<1>(r);
    auto cotpivr = flx::cotpi(vr);
    TTS_ULP_EQUAL(flx::d0(cotpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cotpivr), d1, 4.0);
   }
  {
    auto vr = flx::variable<2>(r);
    auto cotpivr = flx::cotpi(vr);
    TTS_ULP_EQUAL(flx::d0(cotpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cotpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(cotpivr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto cotpivr = flx::cotpi(vr);
    TTS_ULP_EQUAL(flx::d0(cotpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cotpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(cotpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(cotpivr), d3, 4.0);
  }
   {
    auto vr = flx::variable<4>(r);
    auto cotpivr = flx::cotpi(vr);
    TTS_ULP_EQUAL(flx::d0(cotpivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(cotpivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(cotpivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(cotpivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(cotpivr), d4, 8.0);
  }
};
