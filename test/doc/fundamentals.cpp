#include <flx/flx.hpp>
#include <iostream>

using wide_ft  = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft x   = {-1.0f, 2.0f, -3.0f,  0.0f};
  auto vx(flx::var(x));
  auto vy(vx);
  auto vz =  vx;
  auto av = eve::average(vx, vy);

  std::cout << "---- simd" << '\n'
            << "<- x   = " << x << '\n'
            << "<- vx  = " << vx << '\n'
            << "-> vy  = " << vy << '\n'
            << "-> vz  = " << vz << '\n'
            << "-> av  = " << av << '\n'
    ;

  auto sx(flx::var(-2.5));
  auto sy = sx;
  std::cout << "---- scalar" << '\n'
            << "<- sx   = " << sx << '\n'
            << "-> sy   = " << sy << '\n';
  return 0;
}
