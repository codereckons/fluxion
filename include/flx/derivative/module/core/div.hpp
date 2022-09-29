//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{

  template<floating_value T, floating_value U>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T , U y ) noexcept
  {
    using r_t = common_compatible_t<T, U>;
    return rec(r_t(y));
  }

  template<floating_value T, floating_value U>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<2> const &
                                    , T x, U y ) noexcept
  {
    using r_t = common_compatible_t<T, U>;
    return -rec(sqr(r_t(y)))*r_t(x);
  }

  template<auto N, typename T0, typename T1, typename... Ts>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
                           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      r_t h = mul(r_t(arg1), r_t(args)...);
      if constexpr(N==1) return  rec(h);
      else {
        h = -r_t(arg0)/h;
        if constexpr(N==2) return  h/r_t(arg1);
        else
        {
          auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
            {
              auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
              {
                if constexpr(J==N) that = val;
              };

              ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
            };
          r_t that(0);
          getNth(std::make_index_sequence<sizeof...(args)>{},that,r_t(args)...);
          return h/that;
        }
      }
    }
  }
}
