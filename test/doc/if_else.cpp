#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  auto inf = eve::inf(eve::as<float>());

  wide_ft x = {-1.0f, 7.5f, inf,  0.1f};
  auto f = [](auto e){return eve::if_else (e < 4, eve::sqr(e), -e);};
  std::cout << "---- scalar" << '\n'
            << "<- x                  = " << x << '\n'
            << "<- f(x)               = " << f(x) << '\n'
            << "-> val(f(var(x)))     = " << flx::val(f(flx::var(x))) << '\n'
            << "-> der(f(var(x)))     = " << flx::der(f(flx::var(x))) << '\n';
  return 0;
}
