//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<auto N, value T, value U>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), flx::derivative_type<N> const &, T const &a, U const &b) noexcept
  -> common_value_t<T, U>
  requires (std::floating_point<underlying_type_t<common_value_t<T, U>>>)
  {
    return arithmetic_call(flx::derivative_type<N>()(div), a, b);
  }

  template<value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<1> const &
                                    , T , T y ) noexcept
  requires(std::floating_point<underlying_type_t<T>>)
  {
    return rec(y);
  }

  template<value T>
  EVE_FORCEINLINE constexpr T div_(EVE_SUPPORTS(cpu_)
                                    , flx::derivative_type<2> const &
                                    , T x, T y ) noexcept
  requires(std::floating_point<underlying_type_t<T>>)
  {

    return -rec(sqr(y))*x;
  }

  template<auto N, value T0, value T1, value... Ts>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
                           , T0 arg0, T1 arg1, Ts... args) noexcept
  requires(std::floating_point<underlying_type_t<common_value_t<T0,T1, Ts...>>>)
  {
    using r_t = common_value_t<T0,T1, Ts...>;
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
