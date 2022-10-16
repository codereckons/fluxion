#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <array>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  using flx::der;
  using flx::val;
  wide_ft x(0.5, 1.0, 1.5, 2.0);
  auto myfunc = [](auto x){return eve::cos(x*eve::sqr(x))*x+eve::exp(x); };
  auto dmyfunc = [](auto x){return -eve::sin(x*eve::sqr(x))*3*eve::sqr(x)*x+ eve::cos(x*eve::sqr(x))+eve::exp(x); };
  auto zz = myfunc(flx::var(x));
  std::cout          << "-> val(myfunc(var(x))) " << val(zz)  << '\n';
  std::cout          << "-> der(myfunc(var(x))) " << der(zz)  << '\n';
  std::cout          << "->    dmyfunc(x)       " << dmyfunc(x)   << '\n';
   return 0;
}
