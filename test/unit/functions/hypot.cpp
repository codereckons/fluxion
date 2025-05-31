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
<typename T>(T r,  T s)
{
  auto dg1 = [](auto x, auto y){ return x/flx::sqrt(x*x+y*y); };
  auto dg2 = [](auto x, auto y){ return y/flx::sqrt(x*x+y*y); };
  auto d2g12 = [](auto x, auto y){ return -x*y/((x*x+y*y)*flx::sqrt(x*x+y*y)); };
  TTS_ULP_EQUAL((flx::D<flx::vars{0}>(flx::hypot)(r, s)), dg1(r, s), 1.0);
  TTS_ULP_EQUAL((flx::D<flx::vars{1}>(flx::hypot)(r, s)), dg2(r, s), 1.0);
  TTS_ULP_EQUAL((flx::D<flx::vars{0, 1}>(flx::hypot)(r, s)), d2g12(r, s), 2.0);

};
