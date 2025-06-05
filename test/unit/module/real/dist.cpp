//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::dist over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T r,  T s)
{
   {
   auto vr = flx::variable<4>(r);
    auto distvr = flx::dist(vr, s);
    TTS_ULP_EQUAL(flx::d0(distvr), eve::abs(r-s), 0.5);
    TTS_ULP_EQUAL(flx::d1(distvr), eve::sign(r-s), 0.5);
    TTS_ULP_EQUAL(flx::d2(distvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(distvr), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(distvr), T(0), 0.5);
  }
  {
   auto vs = flx::variable<4>(s);
    auto distvs = flx::dist(r, vs);
    TTS_ULP_EQUAL(flx::d0(distvs), eve::abs(s-r), 0.5);
    TTS_ULP_EQUAL(flx::d1(distvs), eve::sign(s-r), 0.5);
    TTS_ULP_EQUAL(flx::d2(distvs), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d3(distvs), T(0), 0.5);
    TTS_ULP_EQUAL(flx::d4(distvs), T(0), 0.5);
  }

  {
    auto [a, b] = flx::variable2<0, 1>(r, s);
    auto distvab = flx::dist(a, b);
    TTS_ULP_EQUAL(flx::e0(distvab), eve::abs(s-r), 0.5);
    TTS_ULP_EQUAL(flx::e1(distvab), eve::sign(r-s), 0.5);
    TTS_ULP_EQUAL(flx::e2(distvab), eve::sign(s-r), 0.5);
    TTS_ULP_EQUAL(flx::e12(distvab), T(0), 0.5);
  }
};
