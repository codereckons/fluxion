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
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2
            , T const& ,  T const& , T const& )
{
  if constexpr(std::same_as<T, double>)
  {
//    auto f = [](auto x, auto y,  auto z){return x*y+z; }; //flx::fma(x, y, z); };
//    auto f = [](auto x, auto y,  auto z){return flx::cos((x+y)*z); };
    auto g = [](auto x, auto y,  auto z){return flx::cos(flx::fma(x, flx::add(x, y)*z, y)); };
 //    auto df = [](auto x, auto y,  auto
//                 ,  auto dx, auto dy,  auto dz){
//       return y*dx+x*dy+dz;
//     };

//    auto d = flx::differential(f, a0, a1, a2);
//     auto dif = d(da0, da1, da2);
//    auto ref  = df(a0, a1, a2, da0, da1, da2);
//     TTS_ULP_EQUAL(dif      , ref, 0.5);
//     TTS_ULP_EQUAL(d(1.0, 1.0, 1.0), df(a0, a1, a2, 1.0, 1.0, 1.0), 0.5);
//     TTS_ULP_EQUAL(d(da0, 1.0, 1.0), df(a0, a1, a2, da0, 1.0, 1.0), 0.5);


    auto der0 = flx::d1(g(flx::variable<1>(a0), a1, a2));
    auto der1 = flx::d1(g(a0, flx::variable<1>(a1), a2));
    auto der2 = flx::d1(g(a0, a1, flx::variable<1>(a2)));
    auto gg = flx::gradient(g, a0, a1, a2);
    std::cout << "toto " << gg << std::endl;
    TTS_ULP_EQUAL(get<0>(gg), der0, 0.5);
    TTS_ULP_EQUAL(get<1>(gg), der1, 0.5);
    TTS_ULP_EQUAL(get<2>(gg), der2, 0.5);
//     TTS_ULP_EQUAL(ref, g[0]*da0+g[1]*da1+g[2]*da2, 0.5);
  }
};
