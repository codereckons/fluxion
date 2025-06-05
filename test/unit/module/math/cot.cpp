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

TTS_CASE_WITH ( "Check flx::cot over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::cot(data), eve::cot(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::cot over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(2, 5))
              )
<typename T>(T r)
{
  auto vr = flx::variable<4>(r);
  auto d0 = eve::cot(r);
  auto d1 = -eve::sqr(eve::csc(r));
  auto d2 = -2*eve::cot(r)*d1;
  auto d3 = -2*(eve::sqr(d1) - 2 *eve::sqr(d0)*d1);
  auto d4 = -8*d0*d1*(eve::sqr(d0)-2*d1);

  auto cotvr = flx::cot(vr);
  TTS_ULP_EQUAL(flx::d0(cotvr), d0, 4.0);
  TTS_ULP_EQUAL(flx::d1(cotvr), d1, 4.0);
  TTS_ULP_EQUAL(flx::d2(cotvr), d2, 4.0);
  TTS_ULP_EQUAL(flx::d3(cotvr), d3, 4.0);
  TTS_ULP_EQUAL(flx::d4(cotvr), d4, 4.0);
};
