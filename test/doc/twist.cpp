//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>
// #include <fluxion/details/kumi_utils.hpp>


// template <auto I,  auto J, unsigned short Order, typename ...Xs>
// constexpr auto variable2(Xs... xi) noexcept
// {
//   auto k = kumi::tuple{xi...};
//   using t_t = decltype((xi+...));
//   using r_t = flx::as_hyperdual_n_t<Order+1, t_t>;
//   auto h = flx::_::powersof2<Order+1, t_t>();
//   auto x = get<I>(k);
//   if constexpr(I == J)
//   {
//     kumi::get<0>(h) = x;
//     std::cout << "h " << h << std::endl;
//     r_t hvx(h);
//     auto kx = kumi::replace(k, hvx, kumi::index<I>);
//     return kx;
//   }
//   else
//   {
//     auto y = get<J>(k);
//     std::cout << "h   "<< h << std::endl;
//     auto h0 = kumi::fill<flx::dimension_v<r_t>/2>(eve::zero(eve::as<t_t>()));
//     auto hx = cat(kumi::extract(h, kumi::index<0>, kumi::index<flx::dimension_v<r_t>/2>), h0);
//     auto hy = cat(h0, kumi::extract(h, kumi::index<flx::dimension_v<r_t>/2>));
//     kumi::get<0>(hx) = x;
//     kumi::get<0>(hy) = y;
//     std::cout << "hx " << hx << std::endl;
//     std::cout << "hy " << hy << std::endl;
//     r_t hvx(hx);
//     r_t hvy(hy);
//     auto kx = kumi::replace<I>(k, hvx, kumi::index<I>);
//     auto kxy = kumi::replace<J>(kx, hvy, kumi::index<J>);
//     return kxy;
//   }
// }


int main()
{
  double x = 10.0;
  double y = -2.3;
  // auto [a, b] =  flx::variable2<0, 1, 1>(x, y);
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
  auto ab =  flx::variable2<1, 1, 1>(x, y);
  auto D22f =  0.0;
  auto d22f = kumi::apply(f, ab);

  std::cout << "d22f = " << d22f << std::endl;

  std::cout << flx::e12(d22f) <<  "==" << D22f << std::endl;
  {
  std::cout << " ================================= " << std::endl;
  auto ab =  flx::variable2<0, 0, 1>(x, y);
  auto D11f =  2*y;
  auto d11f = kumi::apply(f, ab);

  std::cout << "d11f = " << d11f << std::endl;

  std::cout << flx::e12(d11f) <<  "==" << D11f << std::endl;
  }

};
