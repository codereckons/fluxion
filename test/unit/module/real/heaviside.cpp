//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <eve/module/core.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::copysign_abs over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(-1, 1)
                            , tts::randoms(-1, 1))
              )
<typename T>(T x ,  T y)
{
  auto  f = [](auto x,  auto y){ return flx::heaviside(x, y); };
  {
    TTS_ULP_EQUAL((flx::D<flx::vars{0}>(f)(x, y)),   T(0), 0.5);
    TTS_ULP_EQUAL((flx::D<flx::vars{1}>(f)(x, y)),   T(0), 0.5);
    TTS_ULP_EQUAL((flx::D<flx::vars{0,1}>(f)(x, y)), T(0), 0.5);
    TTS_ULP_EQUAL((flx::D<flx::vars{1,1}>(f)(x, y)), T(0), 0.5);
    TTS_ULP_EQUAL((flx::D<flx::vars{0,0}>(f)(x, y)), T(0), 0.5);
  }

};
