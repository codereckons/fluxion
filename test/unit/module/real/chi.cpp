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

TTS_CASE_WITH ( "Check flx::chi over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10)
                            , tts::randoms(-10,0)
                            , tts::randoms( 0,10))
              )
(auto data, auto lo,  auto hi)
{
  TTS_EQUAL(flx::chi(data, lo, hi), eve::chi(data, lo, hi));
};

TTS_CASE_WITH ( "Check flx::chi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,0)
                            , tts::randoms( 0,10))
              )
<typename T>(T r, T lo,  T hi)
{
  auto d0   = eve::chi(r, lo, hi);
  auto d1 = T(0);
  auto d2 = T(0);
  auto d3 = T(0);
  auto d4 = T(0);
  {
    auto vr = flx::variable<1>(r);
    auto chivr = flx::chi(vr, lo, hi);
    TTS_ULP_EQUAL(flx::d0(chivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(chivr), d1, 4.0);
  }
  {
    auto vr = flx::variable<2>(r);
    auto chivr = flx::chi(vr, lo, hi);
    TTS_ULP_EQUAL(flx::d0(chivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(chivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(chivr), d2, 4.0);
  }
  {
    auto vr = flx::variable<3>(r);
    auto chivr = flx::chi(vr, lo, hi);
    TTS_ULP_EQUAL(flx::d0(chivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(chivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(chivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(chivr), d3, 4.0);
  }
  {
    auto vr = flx::variable<4>(r);
    auto chivr = flx::chi(vr, lo, hi);
    TTS_ULP_EQUAL(flx::d0(chivr), d0, 4.0);
    TTS_ULP_EQUAL(flx::d1(chivr), d1, 4.0);
    TTS_ULP_EQUAL(flx::d2(chivr), d2, 4.0);
    TTS_ULP_EQUAL(flx::d3(chivr), d3, 4.0);
    TTS_ULP_EQUAL(flx::d4(chivr), d4, 8.0);
  }
};
