#include <flx/flx.hpp>
#include <eve/module/core.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft x = {3, 4, 5, 6};
  wide_ft y = {1, 2, 3, 4};
  wide_ft z = {5, 6, 7, 8};
  std::cout << "---- scalar" << '\n'
            << "<- x                                   = " << x << '\n'
            << "<- y                                   = " << y << '\n'
            << "<- z                                   = " << z << '\n'
            << "<- eve::average(x, y, z)               = " << eve::average(x, y, z) << '\n'
            << "-> val(eve::average(var(x), y, z))          = " << flx::val(eve::average(flx::var(x), y, z)) << '\n'
            << "-> der(flx::average(x, var(y), z))          = " << flx::der(eve::average(x, flx::var(y), z)) << '\n'
            << "-> der(flx::average(x, y, var(z)))          = " << flx::der(eve::average(x, y, flx::var(z))) << '\n'
            << "-> der(flx::average(x, var(y), var(z)))     = " << flx::der(eve::average(x, flx::var(y), flx::var(z))) << '\n'
            << "-> der(flx::average(var(x), var(y), var(z)))= " << flx::der(eve::average(flx::var(x), flx::var(y), flx::var(z))) << '\n'
    ;
  return 0;
}
