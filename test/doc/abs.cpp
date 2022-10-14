#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft  = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft x   = {-1.0f, 2.0f, -3.0f,  0.0f};
  auto vx(flx::var(x));

  std::cout << "---- simd" << '\n'
            << "<- x            = " << x << '\n'
            << "<- vx           = " << vx << '\n'
            << "-> abs(vx)      = " << eve::abs(vx) << '\n';

  auto sx(flx::var(-2.4));

  std::cout << "---- scalar" << '\n'
            << "<- sx        = " << sx << '\n'
            << "-> abs(sx)   = " << eve::abs(sx) << '\n';
  return 0;
}
