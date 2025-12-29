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
  double z = 2.5;
  auto f = [](auto x, auto y, auto z){return x*x+y*y+z*z; };
  std::cout << f(z, 2*z, 3*z) << std::endl;
  auto ff = [](auto ... xi){return kumi::tuple{xi...}; };
  std::cout << ff(z, 2*z, 3*z) << std::endl;
  std::cout << ff(z, flx::variable<1>(2*z), 3*z) << std::endl;
  constexpr auto Ord = 1;
  auto compute = [&]<auto I>(kumi::index_t<I>, auto ... xi){
    auto values = kumi::tuple{xi...};

    auto h = kumi::extract(values, kumi::index<I>, kumi::index<I+1>);
      if constexpr(I == 0){
        auto cor_value = cat(h , kumi::extract(values, kumi::index<I+1>));
        return flx::d<Ord>(kumi::apply(f, cor_value));// d<Ord>(kumi::apply(f, cor_value));
      }
      else  if  constexpr(I+1 == kumi::size_v<decltype(values)>)
      {
        auto cor_value = cat(kumi::extract(values, kumi::index<0>, kumi::index<I>), h);
        return flx::d<Ord>(kumi::apply(f, cor_value));// d<Ord>(kumi::apply(f, cor_value));
      }
      else
      {
        auto cor_value = cat(kumi::extract(values, kumi::index<0>,kumi::index<I>)
                            , h
                            , kumi::extract(values, kumi::index<I+1>));
        return flx::d<Ord>(kumi::apply(f, cor_value)); //d<Ord>(kumi::apply(f, cor_value));
      }
    };

std::cout << (compute(kumi::index_t<1>{}, z, 2*z, 3*z)) << std::endl;
std::cout << (compute(kumi::index_t<0>{}, flx::variable<1>(z), 2*z, 3*z)) << std::endl;
std::cout << (compute(kumi::index_t<1>{}, z, flx::variable<1>(2*z), 3*z)) << std::endl;
std::cout << (compute(kumi::index_t<2>{}, z, 2*z, flx::variable<1>(3*z))) << std::endl;
std::cout << flx::D<flx::vars{0, 1}>(f)(z, 2*z, 3*z) << std::endl;
std::cout << flx::D<flx::vars{1, 1}>(f)(z, 2*z, 3*z) << std::endl;
std::cout << flx::D<flx::vars{2, 1}>(f)(z, 2*z, 3*z) << std::endl;
std::cout << flx::D<flx::vars{0, 2}>(f)(z, 2*z, 3*z) << std::endl;
std::cout << flx::D<flx::vars{1, 2}>(f)(z, 2*z, 3*z) << std::endl;
std::cout << flx::D<flx::vars{2, 2}>(f)(z, 2*z, 3*z) << std::endl;

};
