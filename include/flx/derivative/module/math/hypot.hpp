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
//   template < auto N, typename ...Ts>
//   auto getNth(std::integral_constant<std::size_t,N>, auto ...xs){
//     using r_t = common_compatible_t<Ts...>;
//     if constexpr(N > sizeof...(Ts)+2)
//     {
//       return zero(as<r_t >());
//     }
//     else
//     {
//       auto gn = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs){
//         auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
//         {
//           if constexpr(J==N) that = val;
//         };

//         ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
//       };
//       r_t that(0);
//       gn(std::make_index_sequence<sizeof...(xs)>{},that,r_t(xs)...);
//       return that;
//     }
//   }

  template<auto N, floating_real_value T0, floating_real_value T1, floating_real_value... Ts>
  EVE_FORCEINLINE constexpr auto hypot_(EVE_SUPPORTS(cpu_)
                                       , flx::derivative_type<N> const &
                                       , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      auto h = hypot(arg0, arg1, args...);
      if constexpr(N==1)       return arg0/h;
      else if constexpr(N==2)  return  arg1/h;
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
        return that/h;
      }
    }
  }

  template<int N, typename T0, typename T1, typename... Ts>
  auto hypot_(EVE_SUPPORTS(cpu_), decorated<flx::derivative_<N>(pedantic_)> const &
             , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else
    {
      if constexpr(N > sizeof...(Ts)+2) return zero(as<r_t>());
      else
      {
        auto h = pedantic(hypot)(arg0, arg1, args...);
        if constexpr(N==1)       return arg0/h;
        else if constexpr(N==2)  return  arg1/h;
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
          return that/h;
        }
      }
    }
  }

}
