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

TTS_CASE_WITH ( "Check flx::tanpi over real"
              , flx::real_types
              , tts::generate(tts::randoms(1,10))
              )
(auto data)
{
  TTS_ULP_EQUAL(flx::tanpi(data), eve::tanpi(data), 2.5);
};

TTS_CASE_WITH ( "Check flx::tanpi over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-0.25, 0.25))
              )
<typename T>(T r)
{
//  auto pr = tts::prec<T>(1.0e-3, 1.0e-7);
  auto pi = eve::pi(eve::as(r));
  auto vr = flx::variable<4>(r);
  auto ref = flx::tan(pi*vr);
  auto d0 = eve::tanpi(r);
  auto d1 = flx::d1(ref);
  auto d2 = flx::d2(ref);
  auto d3 = flx::d3(ref);
  auto d4 = flx::d4(ref);
  auto tanpivr = flx::tanpi(vr);
  TTS_ULP_EQUAL(flx::d0(tanpivr), d0, 20.0);
  TTS_ULP_EQUAL(flx::d1(tanpivr), d1, 20.0);
  TTS_ULP_EQUAL(flx::d2(tanpivr), d2, 20.0);
  TTS_ULP_EQUAL(flx::d3(tanpivr), d3, 20.0);
  TTS_ULP_EQUAL(flx::d4(tanpivr), d4, 20.0);
};
