//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>
#include <eve/algo.hpp>

namespace eve::detail
{

  template<auto N, value T0, value T1>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
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
      EVE_ASSERT( N == 1, "reverse_horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }

  template<auto N, value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , flx::derivative_type<N> const &
                                                , T0 const & b, T1 const &, T2 const &) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    if constexpr(N == 1)
    {
      return r_t(b);
    }
    else
    {
      EVE_ASSERT( N == 1, "reverse_horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }

  //================================================================================================
  //N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<auto N, value T0,  value T1, value ...Ts>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , flx::derivative_type<N> const &
                                                , T0 xx, T1 , Ts... cs) noexcept
  {
    using r_t = common_compatible_t<T0, Ts...>;
    if constexpr(N == 1)
    {
      auto x = r_t(xx);
      auto n = 0;
      std::array<r_t, sizeof...(cs)> c {(r_t(cs)*++n)...};
      return reverse_horner(x, c);
   }
    else
    {
      EVE_ASSERT( N == 1, "reverse_horner derivative is only implemented relative to first parameter");
      return nan(as<r_t>());
    }
  }
}
