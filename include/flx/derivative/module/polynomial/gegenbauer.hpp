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

  template<integral_value N, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto gegenbauer_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<1> const &
                                            , N const &n
                                            , T const &l
                                            , U const &x) noexcept
  requires index_compatible_values<N, T> && compatible_values<T, U>
  {
    auto iseqzn = is_eqz(n);
    return if_else(iseqzn, zero, 2*l*gegenbauer(dec[!iseqzn](n), inc(l), x));
  }
}
