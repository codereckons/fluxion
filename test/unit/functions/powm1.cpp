//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <eve/module/math.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::powm1 over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2.0)
                            , tts::randoms(0.5, 2.0))
              )
<typename T>(T x ,  T y)
{
    auto   f = [](auto x,  auto y){return flx::powm1(x, y); };
    auto d1f = [](auto x,  auto y){return y*eve::pow(x-1, y-1);};
    auto d2f = [](auto x,  auto y){return eve::log(x)*eve::pow(x, y); };
    auto d12f= [](auto x,  auto y){return eve::inc(y*eve::log(x-1))*eve::pow(x-1, y-1); };
    auto d11f= [](auto x,  auto y){return   y*(y-1)*eve::pow(x-1, y-2); };
    auto d22f= [](auto x,  auto y){return eve::sqr(eve::log(x-1))*eve::pow(x-1, y); };
  {
    TTS_ULP_EQUAL((flx::derivate<0,1>(f, x, y)),     d1f(x, y), 20);
    TTS_ULP_EQUAL((flx::derivate<1,1>(f, x, y)),     d2f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<flx::vars{0,1}>(f)(x, y)), d12f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<flx::vars{1,1}>(f)(x, y)), d22f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<flx::vars{0,0}>(f)(x, y)), d11f(x, y), 200);
    TTS_ULP_EQUAL((flx::derivate<0,2>(f, x, y)),     d11f(x, y), 200);
    TTS_ULP_EQUAL((flx::derivate<1,2>(f, x, y)),     d22f(x, y), 20);
  }
//   {
//     int n = 5;
//     TTS_ULP_EQUAL((flx::derivate<0,1>(f, x, n)),     d1f(x, n), 20);
//     TTS_ULP_EQUAL((flx::derivate<1,1>(f, x, n)),     d2f(x, n), 20);
//     TTS_ULP_EQUAL((flx::D<flx::vars{0,1}>(f)(x, n)), d12f(x, n), 20);
//     TTS_ULP_EQUAL((flx::D<flx::vars{1,1}>(f)(x, n)), d22f(x, n), 20);
//     TTS_ULP_EQUAL((flx::D<flx::vars{0,0}>(f)(x, n)), d11f(x, n), 20);
//     TTS_ULP_EQUAL((flx::derivate<0,2>(f, x, n)),     d11f(x, n), 20);
//     TTS_ULP_EQUAL((flx::derivate<1,2>(f, x, n)),     d22f(x, n), 20);
//   }
};
