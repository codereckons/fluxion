//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>


int main()
{

  double x = 10.0;
  double y = -2.3;
  // auto [a, b] =  flx::variable2<0, 1>(x, y);
  auto a = flx::variable<3>(x);
  auto b = flx::variable<3>(y);
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << "a " << a << std::endl;
  std::cout << "b " << b << std::endl;
  auto f = [](auto x,  auto y){return x*x*y + x*y; };
  auto D12f =  2*x+1;
  auto d12f = f(a, b);
  std::cout << "f(a, b) " << d12f << std::endl;
  std::cout << flx::e12(d12f) <<  "==" << D12f << std::endl;

  std::cout << " ================================= " << std::endl;
  auto ab =  flx::variable2<1, 1>(x, y);
  auto D22f =  0.0;
  auto d22f = kumi::apply(f, ab);

  std::cout << "d22f = " << d22f << std::endl;

  std::cout << flx::e12(d22f) <<  "==" << D22f << std::endl;
  {
  std::cout << " ================================= " << std::endl;
  auto ab =  flx::variable2<0, 0>(x, y);
  auto D11f =  2*y;
  auto d11f = kumi::apply(f, ab);

  std::cout << "d11f = " << d11f << std::endl;

  std::cout << flx::e12(d11f) <<  "==" << D11f << std::endl;
  }

};
