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
  mul_(EVE_SUPPORTS(cpu_), flx::derivative_type<N> const &, T const &a, U const &b) noexcept
  -> common_value_t<T, U>
  {
    return arithmetic_call(flx::derivative_nth<N>(mul), a, b);
  }

  template<value T>
  EVE_FORCEINLINE constexpr T mul_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<1> const &
                                  , T , T y ) noexcept
  {
    return y;
  }

  template<value T>
  EVE_FORCEINLINE constexpr T mul_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<2> const &
                                  , T x, T  ) noexcept
  {

    return x;
  }

  template<auto N, value T0, value T1, value... Ts>
  auto mul_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
 -> common_value_t<T0, T1, Ts...>
  {
  {
    auto mmul = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
      {
        auto iff = []<std::size_t J>(auto acc, auto val, std::integral_constant<std::size_t,J>)
        {
          if constexpr(J==N) return acc; else return acc*val;
        };

        ((that = iff(that,vs, std::integral_constant<std::size_t,I+3>{})),...);
      };
    using r_t = common_value_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else if constexpr(N== 1)
    {
      return r_t{mul(arg1, args...)};
    }
    else if constexpr(N==2)
    {
      return r_t{mul(arg0, args...)};
    }
    else
    {
      auto that = arg0*arg1;
      mmul(std::make_index_sequence<sizeof...(args)>{},that,args...);
      return that;
    }
  }
}
