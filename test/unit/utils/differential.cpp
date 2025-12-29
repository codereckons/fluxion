//======================================================================================================================
/*
  Hypdu - Hyperdual numbers
  Copyright : HYPDU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
#include <test.hpp>
#include <eve/module/math.hpp>

TTS_CASE_WITH( "Check behavior of flx::differential"
        , flx::real_types
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2
                        , T const& da0,  T const& da1, T const& da2)
{
  if constexpr(std::same_as<T, double>)
  {
    auto f = [](auto x, auto y,  auto z){return x*y+z; }; //flx::fma(x, y, z); };
    auto ddf = [](auto x, auto y,  auto
                ,  auto dx, auto dy,  auto dz){
      return y*dx+x*dy+dz;
    };

//    auto d = flx::differential(f, a0, a1, a2);
//     auto dif = d(da0, da1, da2);
    auto ref  = ddf(a0, a1, a2, da0, da1, da2);
    std::cout << ref << std::endl;
//     TTS_ULP_EQUAL(dif      , ref, 0.5);
//     TTS_ULP_EQUAL(d(1.0, 1.0, 1.0), df(a0, a1, a2, 1.0, 1.0, 1.0), 0.5);
//     TTS_ULP_EQUAL(d(da0, 1.0, 1.0), df(a0, a1, a2, da0, 1.0, 1.0), 0.5);


//     auto der0 = flx::d1(f(flx::variable<1>(a0), a1, a2));
//     auto der1 = flx::d1(f(a0, flx::variable<1>(a1), a2));
//     auto der2 = flx::d1(f(a0, a1, flx::variable<1>(a2)));
//    auto diff =  der0*da0+der1*da1+der2*da2;
     auto df = flx::differential(f, a0, a1, a2);
//     std::cout << tts::typename_<decltype(df)> << std::endl;
   TTS_ULP_EQUAL(df(da0, da1, da2), ref, 0.5);
//    {
//      //    auto pipo = kumi::tuple(da0, da1, da2);
//      auto g = flx::gradient(f, a0, a1, a2);
//      auto df = [g](auto const &... dxs){
//        auto tdxs = kumi::tuple{dxs...};
//        auto prod = [](auto l,  auto r){ return l*r; };
//        return kumi::sum(kumi::map(prod, g, tdxs));
//      };
//      std::cout << df(da0, da1, da2) << std::endl;
//    }
  }
};
