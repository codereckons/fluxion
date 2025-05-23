//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::D3 over base"
              , flx::scalar_real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T x, T y, T z)
{

  auto f = [](auto x, auto y, auto z){return x*x*y*y*z*z+x*z*z*y; };

  TTS_EQUAL((flx::D2<0, 1>(f))(x, y, z), 4*x*y*z*z+z*z);
  TTS_EQUAL((flx::D2<0, 0>(f))(x, y, z), 2*y*y*z*z);

  TTS_EQUAL((flx::D3<0, 0, 0>(f))(x, y, z), T(0));
  TTS_EQUAL((flx::D3<0, 1, 2>(f))(x, y, z), 8*x*y*z+2*z);

  TTS_EQUAL((flx::D3<0, 0, 2>(f))(x, y, z), 4*y*y*z);
  TTS_ULP_EQUAL((flx::D3<0, 2, 2>(f))(x, y, z), 4*x*y*y, 1.0);
  TTS_ULP_EQUAL((flx::D3<0, 1, 1>(f))(x, y, z), 4*x*z*z, 1.0);

  auto g = [](auto x){return x*x*x*x; };
  TTS_ULP_EQUAL((flx::D2<0, 0>(g))(x), 12*x*x, 1.0);
};
