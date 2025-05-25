//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
//#include <test.hpp>
#include <array>
#include <iostream>

// template<auto Vars,int Order>
// struct DD;

// template<int Var,int Order>
// struct DD<Var,Order>
// {};

// template<std::size_t N>
// using vars = std::array<int,N>;

// template<std::size_t N, vars<N> Vars, int Order>
// struct DD<Vars, Order>
// {
//     template<typename Func> constexpr auto operator()(Func f) noexcept
//     {
//       if constexpr(N == 1)
//       {
//         std::cout << "icitte0" << std::endl;
//         std::cout << Vars[0]  << std::endl;
//         std::cout << f(1.0, 2.0, 3.0) <<  std::endl;
//         return [f](auto ... xi){
//           return flx::e1(kumi::apply(f, flx::variable1<Vars[0]>(xi...)));
//         };
//       }
//       else if constexpr(N == 2)
//       {
//         std::cout << "icitte1" << std::endl;
//         std::cout << Vars[0] << "  " << Vars[1] << std::endl;
//         std::cout << f(1.0, 2.0, 3.0) <<  std::endl;
//         return [f](auto ... xi){
//           return flx::e12(kumi::apply(f, flx::variable2<Vars[0], Vars[1]>(xi...)));
//         };
//       }
//       else if constexpr(N == 3)
//       {
//         return [f](auto ... xi){
//           return flx::e123(kumi::apply(f, flx::variable3<Vars[0], Vars[1], Vars[2]>(xi...)));
//         };
//       }
//       //return f;
//     }
// };



int main()
{
  flx::DD<flx::vars{0},1> a;
//  flx::DD<0,2>       b;
  flx::DD<flx::vars{0, 1},2> c;
  auto f = [](auto x, auto y, auto z){return x*x*x*y+y*y*y*x+z*z*y; };
  auto z = a(f);
  std::cout<< z(1.0,2.0,3.0) << std::endl;
  auto z1 = c(f);
  std::cout<< z1(1.0,2.0,3.0) << std::endl;
  std::cout<< flx::D2<0, 1>(f)(1.0, 2.0, 3.0)<< std::endl;
  flx::DDD<flx::vars{0, 1}> d;
  std::cout<< d(f)(1.0,2.0,3.0) << std::endl;
  std::cout<< flx::DDD<flx::vars{0, 1}>{}(f)(1.0,2.0,3.0) << std::endl;
  std::cout<< flx::DDD<0, 3>{}(f)(1.0,2.0,3.0) << std::endl;

  return 0;
}


// TTS_CASE_WITH ( "Check flx::D over base"
//               , flx::real_types
//               , tts::generate(tts::randoms(-10,10)
//                             , tts::randoms(-10,10)
//                             , tts::randoms(-10,10))
//               )
// <typename T>(T , T , T )
// {
//    auto f = [](auto x, auto y, auto z){return x*x+y*y+z*z*y; };
//    auto zz = flx::flx::DD<2, flx::flx::vars{0, 1}>{}(f);

//   TTS_EQUAL(0, 0);
