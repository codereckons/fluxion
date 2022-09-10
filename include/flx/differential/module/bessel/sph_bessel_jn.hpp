//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/bessel.hpp>
#include <eve/detail/hz_device.hpp>

namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , flx::diff_type<1> const &
                                            , I nn
                                            , T x) noexcept
  {
//           std::cout << "x  " << x << std::endl;
//           std::cout << "nn " << nn << std::endl;

    auto improper_n = is_ngez(nn) || is_not_flint(nn);
    auto improper_x = is_ngez(x);
    EVE_ASSERT(eve::any(improper_n), "flx::diff(sph_bessel_jn): some orders are non integral positive");
    EVE_ASSERT(eve::any(improper_x), "flx::diff(sph_bessel_jn): some x are negative");
    auto n = convert(nn, as<element_type_t<T>>());
    n = if_else(improper_n, allbits, n);
    x = if_else(improper_x, allbits, x);
    auto xltthresh = x < 1.0;
    auto br_n0 = [](auto x){
      //     std::cout << "br_n0" << std::endl;
      return  -sph_bessel_j1(x);
    };
    auto br_small = [](auto n,  auto x){
      //    std::cout << "br_small" << std::endl;
      auto r = (n / x) * sph_bessel_jn(n, x) - sph_bessel_jn(n+1, x);
      return if_else(is_nan(r), zero, r);
    };

    auto br_last = [](auto n,  auto x){
    //      std::cout << "br_last" << std::endl;
      n+= half(as(x));
      auto d = rsqrt(2*x*inv_pi(as(x)));
      return (cyl_bessel_jn(n, x)*mhalf(as(x))/x+flx::diff(cyl_bessel_jn)(n, x))*d;
    };

    if constexpr( scalar_value<T> && scalar_value<I>)
    {
      if( improper_x || improper_n ) return nan(as(x));
      if( x == inf(as(x)) ) return zero(as(x));
      if( n == 0) return br_n0(x);
      if( xltthresh ) return br_small(n, x);
      return br_last(n, x);
    }
    else
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r       = if_else(improper_n || improper_x, nan(as(x)), zero);
        auto notdone = is_not_nan(r);
       //     std::cout << "notdone 0 "<< notdone << "r " << r << std::endl;
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_small, notdone, xltthresh, r, n, x);
         //     std::cout << "notdone 1 "<< notdone << "r " << r  << std::endl;
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_n0, notdone, is_eqz(n), r, x);
            //    std::cout << "notdone 2 "<< notdone << "r " << r  << std::endl;
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_last, notdone, r, n, x);
             //     std::cout << "notdone 3 "<< notdone  << "r " << r << std::endl;
            }
          }
        }
        r = if_else(is_infinite(x), zero, r);
        return r;
      }
      else return apply_over(flx::diff(sph_bessel_jn), n, x);
    }
  }
}
