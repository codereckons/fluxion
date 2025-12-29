//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributomirs & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::minmag over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T a0,  T a1)
{
  auto f = [](auto x,  auto y){return flx::if_else(flx::is_less(flx::abs(x), flx::abs(y)), x, y);};
  TTS_ULP_EQUAL(                       flx::minmag(a0, a1) ,                      f(a0, a1), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{0}>(flx::minmag)(a0, a1)), (flx::D<flx::vars{0}>(f)(a0, a1)), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::minmag)(a0, a1)), (flx::D<flx::vars{1}>(f)(a0, a1)), 0.5);
};
