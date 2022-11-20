//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/special.hpp>

namespace eve::detail
{
  template<auto N, real_simd_value I, floating_real_value T>
  auto rising_factorial_(EVE_SUPPORTS(cpu_), decorated<flx::derivative_<N>(pedantic_)> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N <= 2)
    {
      auto tmp = pedantic(rising_factorial)(aa, x);
      return flx::derivative_type<N>()(lrising_factorial)(aa, x)*tmp;
    }
    else
      return zero(as<r_t>());
  }

  template<auto N, real_scalar_value I, floating_real_value T, typename D>
  auto rising_factorial_(EVE_SUPPORTS(cpu_), decorated<flx::derivative_<N>(D)> const &
             , I a, T x) noexcept
  {
    if constexpr(N <= 2)
    {
      auto tmp = pedantic(rising_factorial)(T(a), x);
      return flx::derivative_type<N>()(lrising_factorial)(T(a), x)*tmp;
    }
    else
      return zero(as<T>());
  }

  template<auto N, real_value I, floating_real_value T>
  auto rising_factorial_(EVE_SUPPORTS(cpu_)
                        , flx::derivative_type<N> const & d
                        , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N <= 2)
    {
      auto tmp = rising_factorial(aa, x);
      return lrising_factorial(d, aa, x)*tmp;
    }
    else
      return zero(as<r_t>());
  }
}
