//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/polynomial.hpp>
#include <boost/math/special_functions/gegenbauer.hpp>

namespace eve::detail
{

  template<auto I, integral_value N, value T, value U>
  EVE_FORCEINLINE constexpr auto gegenbauer_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<I> const &
                                            , N const &n
                                            , T const &l
                                            , U const &x) noexcept
  {
    using f_t = indexed_common_value_t<N, T, U>;
    if constexpr(I == 3)
    {
      auto iseqzn = is_eqz(n);
      return if_else(iseqzn, zero, 2*l*gegenbauer(dec[!iseqzn](n), inc(l), x));
    }
    else
      return zero(as<f_t>());
  }
}
