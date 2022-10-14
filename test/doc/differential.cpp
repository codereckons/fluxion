#include <flx/flx.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  auto f = [](auto x, auto y,  auto z){return eve::fma(x, y, z); };
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};
  wide_ft z = {5, 6, 7, 8};
  wide_ft dx = {1.0, 0.5, 0.1, 0.2};
  wide_ft dy = {0.0, 1.0, -3.0, 2.0};
  wide_ft dz = {1.0, 2.0, -1.0, 2.0};
  auto zz = flx::d(f, x, y, z);
  std::cout << "---- simd" << std::setprecision(5) << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
            << "<- z                                   = " << z << '\n'
            << "<- dx                                  = " << dx << '\n'
            << "<- dy                                  = " << dy << '\n'
            << "<- dz                                  = " << dz << '\n'
            << "<- d(f, x, y, z)(dx, dy, dz)           = " << zz(dx, dy, dz) << '\n'
    ;

  auto g = flx::gradient(f, x, y, z);
  std::cout << "gradient of f is : {";
  for(int i=0; i < 2 ; ++i)
  {
    std::cout << g[i] << ", ";
  }
  std::cout << g[2] << "}" << '\n'   ;

  std::cout << " < {gx, gy, gz}, {dx, dy, dz} >        = "<< g[0]*dx+g[1]*dy+g[2]*dz << '\n'   ;
  return 0;
}
