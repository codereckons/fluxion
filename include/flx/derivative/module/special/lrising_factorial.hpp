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
  template<auto N, ordered_value I, floating_ordered_value T, typename D>
  auto lrising_factorial_(EVE_SUPPORTS(cpu_), decorated<flx::derivative_<N>(D)> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N == 1)
    {
      return digamma(aa+x) - digamma(aa);
    }
    else if constexpr(N == 2)
    {
      return digamma(aa+x);
    }
    else
      return zero(as<r_t>());
  }

  template<auto N, ordered_value I, floating_ordered_value T>
  auto lrising_factorial_(EVE_SUPPORTS(cpu_), flx::derivative_type<N> const &
             , I a, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    using r_t = as_wide_t<elt_t, cardinal_t<I>>;
    auto aa = convert(a, as(elt_t()));
    if constexpr(N == 1)
    {
      return digamma(aa+x) - digamma(aa);
    }
    else if constexpr(N == 2)
    {
      return digamma(aa+x);
    }
    else
      return zero(as<r_t>());
  }

}
