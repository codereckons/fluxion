//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto logspace_add_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<1> const &
                                   , T const &x
                                   , U const &y) noexcept
  {
    return rec(inc(exp(y-x)));
  }

   template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto logspace_add_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<2> const &
                                   , T const &x
                                   , U const &y) noexcept
  {
    return  rec(inc(exp(x-y)));
  }

  //===============================================================================================
  // Multi case
  //================================================================================================
  template<int N, typename T0, typename T1, typename... Ts>
  auto logspace_add_(EVE_SUPPORTS(cpu_), flx::derivative_type<N>
                    , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
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
      getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
      auto z = exp(arg0-that)+exp(arg1-that);
      return eve::rec(z+(...+exp(args-that)));
    }
  }
}
