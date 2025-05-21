//======================================================================================================================
/*
  Hypdu - Hyperdual numbers
  Copyright : HYPDU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>

TTS_CASE_WITH( "Check behavior of flx::gradient"
        , flx::real_types
        , tts::generate ( tts::randoms(0.5, 2.0)
                        , tts::randoms(0.5, 2.0)
                        )
        )
<typename T>(T const& x, T const& y )
{
  if constexpr(std::same_as<T, double>)
  {
    auto   f = [](auto x,  auto y){return flx::atan2(x, y); };
    std::cout << f(x, y) << std::endl;
//     auto d1f = [](auto x,  auto y){return  -y/(x*x+y*y); };
//     auto d2f = [](auto x,  auto y){return  x/(x*x+y*y); };
//     auto d12f= [](auto x,  auto y){return  (y*y-x*x)/eve::sqr((x*x+y*y)); };
//     auto d11f= [](auto x,  auto y){return  2*x*y/eve::sqr((x*x+y*y)); };
//     auto d22f= [](auto x,  auto y){return -2*x*y/eve::sqr((x*x+y*y)); };
 //    auto h = flx::hessian<2>(f);
//     std::cout << tts::typename_<decltype(h)> << std::endl;
    auto hes = flx::hessian(f, x, y);
    std::cout << tts::typename_<decltype(hes)> << std::endl;

//     for(int i=0; i <2 ; ++i)
//     {
//        std::cout << "   ";
//       for(int j=0; j <2 ; ++j)
//       {
//         std::cout << hes[i][j] << "  ";
//       }
//        std::cout <<std::endl;
//     }
//   }
    TTS_EQUAL(0, 0);
  }
};
