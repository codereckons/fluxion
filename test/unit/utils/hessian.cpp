//======================================================================================================================
/*
  Hypdu - Hyperdual numbers
  Copyright : HYPDU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>




namespace flx
{



  template<auto N>
  auto ahessian(auto f)
  {
    auto as_index = kumi::generate<N>([](auto i) { return kumi::index<i>; });
    return kumi::map(   [&](auto e)
                        {
                          return kumi::apply([f](auto i, auto j) { return flx::D2<i,j, 1>(f); }, e);
                        }
                    ,   kumi::cartesian_product(as_index,as_index)
                    );
  }

  template<typename Func, typename ... T>
  auto ahessian(Func f, T... xn)
  {
    constexpr size_t N = sizeof...(T);
    auto h = ahessian<N>(f);

    std::array<std::array<decltype(f(xn...)),N>, N> that = {};
    kumi::for_each_index([&](auto i, auto d)
                         {
                           std::cout << tts::typename_ < decltype(i)> << std::endl;
                           std::cout << tts::typename_ < decltype(N)> << std::endl;
                           constexpr auto r = i % N;
                           //                          constexpr int ii = i;
                           constexpr auto c = int(i)/N;
                           that[r][c] = d(xn...);
                         }, h);

    return that;
  }
}












TTS_CASE_WITH( "Check behavior of flx::gradient"
        , flx::real_types
        , tts::generate ( tts::randoms(0.5, 2.0)
                        , tts::randoms(0.5, 2.0)
                        )
        )
<typename T>(T const& x , T const& y )
{
  if constexpr(std::same_as<T, double>)
  {

//     double x = 10.4;
//     double y = 3.2;
//     auto   f = [](auto x,  auto y){return flx::atan2(x, y); };
//     std::cout << f(x, y) << std::endl;
//     auto hes = flx::ahessian(f, x, y);
//     std::cout << tts::typename_<decltype(hes)> << std::endl;

//     for(auto r : hes)
//     {
//       for(auto c : r)
//         std::cout << c << " ";
//       std::cout << "\n";
//     }
//   }

























    auto   f = [](auto x,  auto y){return flx::atan2(x, y); };
    std::cout << f(x, y) << std::endl;
//     auto d1f = [](auto x,  auto y){return  -y/(x*x+y*y); };
//     auto d2f = [](auto x,  auto y){return  x/(x*x+y*y); };
    auto d12f= [](auto x,  auto y){return  (y*y-x*x)/eve::sqr((x*x+y*y)); };
    auto d11f= [](auto x,  auto y){return  2*x*y/eve::sqr((x*x+y*y)); };
    auto d22f= [](auto x,  auto y){return -2*x*y/eve::sqr((x*x+y*y)); };
    //    auto h = flx::hessian<2>(f);
    //    std::cout << tts::typename_<decltype(h)> << std::endl;
    auto hes = flx::hessian(f, x, y);
    std::cout << tts::typename_<decltype(hes)> << std::endl;
    TTS_ULP_EQUAL(hes[0][1], d12f(x, y), 1.5);
    TTS_ULP_EQUAL(hes[1][1], d22f(x, y), 1.5);
    TTS_ULP_EQUAL(hes[0][0], d11f(x, y), 1.5);
  }
  TTS_EQUAL(0, 0);
};
