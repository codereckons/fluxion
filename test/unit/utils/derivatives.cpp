//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::D over base"
              , flx::real_types
              , tts::generate(tts::randoms(-10,10)
                            , tts::randoms(-10,10)
                            , tts::randoms(-10,10))
              )
<typename T>(T x , T y, T z)
{
  {
    auto f = [](auto x, auto y, auto z){return x*x+y*y+z*z*y; };
    TTS_EQUAL((flx::derivate<0, 1>)(f, x, y, z), 2*x);
    TTS_EQUAL((flx::derivate<1, 1>)(f, x, y, z), 2*y+z*z);
    TTS_EQUAL((flx::derivate<2, 1>)(f, x, y, z), 2*z*y);

    TTS_EQUAL((flx::derivate<0, 2>(f, x, y, z)), T(2));
    TTS_EQUAL((flx::derivate<1, 2>(f, x, y, z)), T(2));
    TTS_EQUAL((flx::derivate<2, 2>(f, x, y, z)), 2*y);
  }
  {
    auto f = [](auto x){return x*x*x*x; };
    auto ds = flx::derivatives<0, 4>(f, x);
    TTS_ULP_EQUAL(ds[0], x*x*x*x, 1.0);
    TTS_ULP_EQUAL(ds[1], 4*x*x*x, 1.0);
    TTS_ULP_EQUAL(ds[2], 12*x*x, 1.0);
    TTS_ULP_EQUAL(ds[3], 24*x, 1.0);
    TTS_ULP_EQUAL(ds[4], T(24), 1.0);
  }
};
