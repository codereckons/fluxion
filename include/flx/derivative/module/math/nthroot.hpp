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
  template<auto N, value T, value I>
  EVE_FORCEINLINE constexpr T nthroot_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<N> const &
                                   , T x, I i) noexcept
  {
    using elt_t = element_type_t<T>;
    auto ti = convert(i, as<elt_t>());
    if constexpr(N == 1)
      return nthroot(x, i)*rec(x*ti);
    else if constexpr(N == 2)
      return nthroot(x, i)*eve::log(x)/sqr(ti);
  }
}
