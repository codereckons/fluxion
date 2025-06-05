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
  auto dmin1=[](auto e, auto f) { return eve::if_else(e < f, eve::one(eve::as(f)), eve::zero); };
  auto dmin2=[](auto e, auto f) { return eve::if_else(e > f, eve::one(eve::as(f)), eve::zero); };
  TTS_ULP_EQUAL( (flx::D<flx::vars{0}>(flx::min)(a0, a1)), dmin1(a0, a1), 0.5);
  TTS_ULP_EQUAL( (flx::D<flx::vars{1}>(flx::min)(a0, a1)), dmin2(a0, a1), 0.5);
};
