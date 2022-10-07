//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/polynomial.hpp>
#include <boost/math/special_functions/gegenbauer.hpp>

namespace eve::detail
{

  template<auto N, value M, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto gegenbauer_(EVE_SUPPORTS(cpu_)
                                            , flx::derivative_type<N> const &
                                            , M const &m
                                            , T const &l
                                            , U const &x) noexcept
  {
    EVE_ASSERT(eve::all(eve:is_flint(m)), "some m are not flint");
    using r_t = common_compatible_t<T, U>;
    using e_t = eve::element_type_t<r_t>;
    auto mm = convert(m, eve::as<e_t>());
    if constexpr(N == 3)
    {
      auto iseqzmm = is_eqz(mm);
      return if_else(iseqzmm, zero, 2*l*gegenbauer(dec[!iseqzmm](m), inc(l), x));
    }
    else
    {
      EVE_ASSERT( N == 3, "gegenbauer derivative is only implemented relative to third parameter");
      return nan(as<r_t>());
    }
  }
}
