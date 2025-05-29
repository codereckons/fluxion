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
  auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
  auto vr = flx::variable<4>(r);
  auto ref = flx::rec(flx::tan(vr));
  auto d0 = eve::cot(r);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);
  {
    auto vr = flx::variable<4>(r);
    auto cotvr = flx::cot(vr);
    TTS_RELATIVE_EQUAL(flx::d0(cotvr), d0, pr);
    TTS_RELATIVE_EQUAL(flx::d1(cotvr), d1, pr);
    TTS_RELATIVE_EQUAL(flx::d2(cotvr), d2, pr);
    TTS_RELATIVE_EQUAL(flx::d3(cotvr), d3, pr);
    TTS_RELATIVE_EQUAL(flx::d4(cotvr), d4, pr);
  }
};
