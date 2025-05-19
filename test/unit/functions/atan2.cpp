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
              , tts::generate(tts::randoms(1, 10)
                            , tts::randoms(1, 10))
              )
<typename T>(T x,  T y)
{
  {
    auto   f = [](auto x,  auto y){return flx::atan2(x, y); };
//     auto d1f = [](auto x,  auto y){return  -y/(x*x+y*y); };
//     auto d2f = [](auto x,  auto y){return  x/(x*x+y*y); };
    auto d12f= [](auto x,  auto y){return  (y*y-x*x)/eve::sqr((x*x+y*y)); };
//     TTS_ULP_EQUAL((flx::D<0, 1>(f)(x, y)), d1f(x, y), 1.5);
//     TTS_ULP_EQUAL((flx::D<1, 1>(f)(x, y)), d2f(x, y), 1.5);
// //  TTS_ULP_EQUAL((flx::D2<0,1,1>(f)(x, y)), d12f(x, y), 1.5); //don't work
//     TTS_ULP_EQUAL((flx::D<0,1>(d2f)(x, y)), d12f(x, y), 102);
//     TTS_ULP_EQUAL((flx::D<1,1>(d1f)(x, y)), d12f(x, y), 10);

  auto z =  f(flx::variable<2>(x), flx::variable<2>(y));
//   std::cout << " z  " << z << std::endl;
//   std::cout << " e12(z) "<< flx::e12(z)/2 << std::endl;
//   std::cout << " df12   "<<  d12f(x, y) << std::endl;
  TTS_RELATIVE_EQUAL(flx::e12(z)/2, d12f(x, y), tts::prec<T>(1.0e-2, 1.0e-6)) <<  (flx::e12(z)/2- d12f(x, y)) << '\n';



  }
};
