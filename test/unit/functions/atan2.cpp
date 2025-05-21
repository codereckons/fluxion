//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check flx::atan2 over hyperduals"
              , flx::real_types
              , tts::generate(tts::randoms(0.5, 2.0)
                            , tts::randoms(0.5, 2.0))
              )
<typename T>(T x ,  T y)
{
  {
    auto   f = [](auto x,  auto y){return flx::atan2(x, y); };
    auto d1f = [](auto x,  auto y){return  -y/(x*x+y*y); };
    auto d2f = [](auto x,  auto y){return  x/(x*x+y*y); };
    auto d12f= [](auto x,  auto y){return  (y*y-x*x)/eve::sqr((x*x+y*y)); };
    auto d11f= [](auto x,  auto y){return  2*x*y/eve::sqr((x*x+y*y)); };
    auto d22f= [](auto x,  auto y){return -2*x*y/eve::sqr((x*x+y*y)); };
    TTS_ULP_EQUAL((flx::D<0,1>(f)(x, y)),    d1f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<1,1>(f)(x, y)),    d2f(x, y), 20);
    TTS_ULP_EQUAL((flx::D2<0,1,1>(f)(x, y)), d12f(x, y), 40);
    TTS_ULP_EQUAL((flx::D2<1,1,1>(f)(x, y)), d22f(x, y), 20);
    TTS_ULP_EQUAL((flx::D2<0,0,1>(f)(x, y)), d11f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<0,2>(f)(x, y)),    d11f(x, y), 20);
    TTS_ULP_EQUAL((flx::D<1,2>(f)(x, y)),    d22f(x, y), 20);
  }

};
