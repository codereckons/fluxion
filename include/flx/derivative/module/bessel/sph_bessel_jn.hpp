//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/bessel.hpp>
#include <eve/detail/hz_device.hpp>

namespace eve::detail
{

  template<auto N, ordered_value I, floating_ordered_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , I nn
                                            , T x) noexcept
  {
    if constexpr(N == 2)
    {
      auto improper_n = is_ngez(nn) || is_not_flint(nn);
      auto improper_x = is_ngez(x);
      EVE_ASSERT(eve::none(improper_n), "flx::derivative(sph_bessel_jn): some orders are non integral positive");
      EVE_ASSERT(eve::none(improper_x), "flx::derivative(sph_bessel_jn): some x are negative");
      auto n = convert(nn, as<element_type_t<T>>());
      n = if_else(improper_n, allbits, n);
      x = if_else(improper_x, allbits, x);
      auto compute = [](auto n,  auto x){
        auto r = (n / x) * sph_bessel_jn(n, x) - sph_bessel_jn(n+1, x);
        return if_else(is_nan(r), zero, r);
      };

      if constexpr( scalar_value<T> && scalar_value<I>)
      {
        if( improper_x || improper_n ) return nan(as(x));
        if( x == inf(as(x)) ) return zero(as(x));
        return compute(n, x);
      }
      else
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto r       = if_else(improper_n || improper_x, nan(as(x)), zero);
          auto notdone = is_not_nan(r);
          r = if_else(notdone,  compute(n, x), r);
          r = if_else(is_infinite(x), zero, r);
          return r;
        }
        else return apply_over(flx::derivative_2nd(sph_bessel_jn), n, x);
      }
    }
    else return T(0);
  }
}
