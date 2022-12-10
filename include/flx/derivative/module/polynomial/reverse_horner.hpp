//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>
#include <eve/algo.hpp>

namespace eve::detail
{

  template<value T0, value T1>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , flx::derivative_type<1> const &
                                                , T0 const &, T1 const &) noexcept
  -> common_value_t<T0, T1>
  {
    using r_t = common_value_t<T0, T1>;
    return zero(as<r_t>());
  }

  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , flx::derivative_type<1> const &
                                                , T0 const & b, T1 const &, T2 const &) noexcept
  -> common_value_t<T0, T1, T2>
  {
    using r_t = common_value_t<T0, T1, T2>;
    return r_t(b);
  }

  //================================================================================================
  //N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , flx::derivative_type<1> const &
                                                , T0 xx, T1 , Ts... cs) noexcept
  -> common_value_t<T0, Ts...>
  {
    using r_t = common_value_t<T0, Ts...>;
    auto x = r_t(xx);
    auto n = 0;
    std::array<r_t, sizeof...(cs)> c {(r_t(cs)*++n)...};
    return reverse_horner(x, c);
  }
}
