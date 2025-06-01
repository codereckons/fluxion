//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::add over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T a0,  T a1)
{
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm(T(1), a0, a1))), eve::sign(a0), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm( 1,   a0, a1))), eve::sign(a0), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm(T(2), a0, a1))), (flx::D<flx::vars{0}>(flx::hypot(a0, a1))), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::lpnorm(  2,  a0, a1))), (flx::D<flx::vars{0}>(flx::hypot(a0, a1))), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1, 2}>(flx::lpnorm(  T(1),  a0, a1))),(flx::D<flx::vars{0, 1}> (flx::manhattan)(a0, a1)), 0.5);
};
