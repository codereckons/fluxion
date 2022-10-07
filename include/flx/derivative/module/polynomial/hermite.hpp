//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{

  template<auto I, value M, floating_real_value T>
  EVE_FORCEINLINE constexpr auto hermite_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<I> const &
                                  , M const &m
                                  , T const &x) noexcept
  {
    EVE_ASSERT(eve::all(eve:is_flint(m)), "some m are not flint");
    using e_t = eve::element_type_t<T>;
    auto mm = convert(m, eve::as<e_t>());
    if constexpr(I == 2)
    {
      EVE_ASSERT(eve::all(is_flint(m)), "some m are not flint");
      auto imm = int_(mm);
      return fma(x+x, eve::hermite(imm, x), -eve::hermite(inc(imm), x));
    }
    else
    {
      EVE_ASSERT(I == 2, "derivative of hermite is only defined relative to the second parameter");
      using r_t = common_compatible_t<T, decltype(mm)>;
      return nan(eve::as<r_t>());
    }
  }
}
