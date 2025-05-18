//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

template <unsigned short Order, flx::concepts::base T>
constexpr auto variable2(T x, T y) noexcept
  {
    using t_t = decltype(x+y);
    using r_t = flx::as_hyperdual_n_t<Order+1, t_t>;
    auto h = flx::_::powersof2<Order+1, t_t>();
    std::cout << "h   "<< h << std::endl;
    auto h0 = kumi::fill<flx::dimension_v<r_t>/2>(eve::zero(eve::as<t_t>()));
    auto hx = cat(kumi::extract(h, kumi::index<0>, kumi::index<flx::dimension_v<r_t>/2>), h0);
    auto hy = cat(h0, kumi::extract(h, kumi::index<flx::dimension_v<r_t>/2>));
    kumi::get<0>(hx) = x;
    kumi::get<0>(hy) = y;
    std::cout << "hx " << hx << std::endl;
    std::cout << "hy " << hy << std::endl;
    r_t hvx(hx);
    r_t hvy(hy);
    return kumi::tuple{hvx, hvy};
  }

int main()
{
  double x = 10.0;
  double y = -2.3;
  auto [a, b] =  variable2<1>(x, y);
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  auto f = [](auto x,  auto y){return x*x*y + x*y; };
  auto D12f =  2*x+1;
  auto d12f = f(a, b);
  std::cout << flx::e12(d12f) <<  "==" << D12f << std::endl;

};
