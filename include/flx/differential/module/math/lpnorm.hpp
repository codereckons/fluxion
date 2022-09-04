//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/differential/diff.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{


  template<int N, real_value P, typename T0, typename T1, typename... Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), flx::diff_type<N>
            , P const & p, T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return flx::diff_type<N>()(lpnorm)(fp, arg0, arg1, args...);
    }
    else
    {
      auto rp = r_t(p);
      if constexpr(N > sizeof...(Ts)+2) return zero(as<r_t>());
      else
      {
        auto tmp = lpnorm(p, arg0, arg1, args...);
        auto h = pow_abs(tmp, r_t(oneminus(p)));
        if constexpr(N==1)       return pow_abs(arg0, dec(rp))*h;
        else if constexpr(N==2)  return pow_abs(arg1, dec(rp))*h;
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
          return pow_abs(that, dec(rp))*h;
        }
      }
    }
  }

  template<int N, real_value P, typename T0, typename T1, typename... Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), decorated<flx::diff_<N>(pedantic_)> const &, P const & p
             , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+2)
    {
      return zero(as<r_t >());
    }
    else if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return decorated<flx::diff_<N>(pedantic_)>()(lpnorm)(fp, arg0, arg1, args...);
    }
    else
    {
      if constexpr(N > sizeof...(Ts)+2) return zero(as<r_t>());
      else
      {
        auto rp = r_t(p);
        auto tmp = pedantic(lpnorm)(p, arg0, arg1, args...);
        auto h =  pow_abs(tmp, r_t(oneminus(p)));
        if constexpr(N==1)       return pow_abs(arg0, dec(rp))*h;
        else if constexpr(N==2)  return pow_abs(arg1, dec(rp))*h;
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
          return pow_abs(that, dec(rp))*h;
        }
      }
    }
  }

}
