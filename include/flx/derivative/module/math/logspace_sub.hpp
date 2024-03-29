//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<value T>
  EVE_FORCEINLINE constexpr T logspace_sub_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &x
                                   , T const &y) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return rec(oneminus(exp(y-x)));
  }

   template<value T>
  EVE_FORCEINLINE constexpr T logspace_sub_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<2> const &
                                   , T const &x
                                   , T const &y) noexcept
   requires(std::floating_point<underlying_type_t<T>>)
  {
    return  rec(oneminus(exp(x-y)));
  }


  //===============================================================================================
  // Multi case
  //================================================================================================
  template<auto N, typename T0, typename T1, typename... Ts>
  auto logspace_sub_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
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
      auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
        {
          auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
          {
            if constexpr(J==N) that = val;
          };

          ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
        };
      r_t that(0);
      if constexpr(N == 1) that = arg0;
      else if constexpr(N == 2) that = arg1;
      else
      {
        getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
      }
      auto z = exp(arg0-that)-exp(arg1-that);
      z = eve::rec(z-(...+exp(args-that)));
      return (N == 1) ? z : -z;
    }
  }
}
