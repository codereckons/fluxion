#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_vdt = eve::wide<flx::valder<float>, eve::fixed<4>>;
using vd_t     = flx::valder<float>;



int main()
{
  auto f = [](auto x){return eve::sub(eve::exp(eve::minus(x)), x);  }; // ok
//  auto f = [](auto x){return eve::exp(eve::minus(x)- x);  };         // ambiguous does not compile
//  auto f = [](auto x){return eve::sub(eve::exp(-x), x);  };          // compile but  false result


  std::cout << "---- scalar" << '\n'
            << "<- newton_raphson(f, 0.5,  eve::eps(as<double>())) = " << flx::newton_raphson(f, 0.5,  eve::eps(eve::as<double>())) << '\n'
           ;

  return 0;
}
