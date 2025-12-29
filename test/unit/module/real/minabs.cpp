//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::minabs over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T a0,  T a1)
{
  auto f = [](auto x,  auto y){return flx::min(flx::abs(x), flx::abs(y));};
  TTS_ULP_EQUAL(                       flx::minabs(a0, a1) ,                      f(a0, a1), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{0}>(flx::minabs)(a0, a1)), (flx::D<flx::vars{0}>(f)(a0, a1)), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::minabs)(a0, a1)), (flx::D<flx::vars{1}>(f)(a0, a1)), 0.5);
};
