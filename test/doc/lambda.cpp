#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <eve/module/complex.hpp>
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
  auto xx = myfunc(flx::var(x));
  std::cout          << "-> val(myfunc(var(x))) " << val(xx)  << '\n';
  std::cout          << "-> der(myfunc(var(x))) " << der(xx)  << '\n';
  std::cout          << "->    dmyfunc(x)       " << dmyfunc(x)   << '\n';

//  using z_t = eve::wide<eve::complex<float>,  eve::fixed<4>>;
  using z_t =           eve::complex<float>;
  auto cx = z_t{1.0, 2.0}; //{x, x};
  auto cxx = myfunc(flx::var(cx));
  std::cout          << "-> val(myfunc(var(cx))) " << val(cxx)  << '\n';
  std::cout          << "-> der(myfunc(var(cx))) " << der(cxx)  << '\n';
  std::cout          << "->    dmyfunc(cx)       " << dmyfunc(cx)   << '\n';

  return 0;
}
