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

  template<auto N, value T0, value T1>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , flx::derivative_type<N> const &
                                        , T0 const &, T1 const &) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    if constexpr(N == 1)
    {
      return zero(as<r_t>());
    }
    else
    {
      EVE_ASSERT( N == 1, "horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }

  template<auto N, value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , flx::derivative_type<1> const &
                                        , T0 const &, T1 const &  b, T2  const &) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    if constexpr(N == 1)
    {
      return r_t(b);
    }
    else
    {
      EVE_ASSERT( N == 1, "horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }

  //================================================================================================
  //N parameters (((..((n-1)*a*x+(n-2)*b)*x+c*(n-3))*x + ..)..)
  //================================================================================================

  template<auto N,
           value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , flx::derivative_type<N> const &
                                        , T0 x, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    if constexpr(N == 1)
    {
      auto n = sizeof...(args)+1;
      r_t that(fma(n*x, a, (n-1)*b));
      --n;
      auto next = [x, &n](auto that, auto arg){
        return --n ? fma(x, that, n*arg) : that;
      };
      ((that = next(that, args)),...);
      return that;
    }
    else
    {
      EVE_ASSERT( N == 1, "horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }
}
