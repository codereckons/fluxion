//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/decorator.hpp>
#include <eve/module/math.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , flx::derivative_type<2> const &
                                  , N const &n
                                  , T const &x) noexcept
  {

    auto nn = convert(n, as<element_type_t<T>>());
    return nn*kind_2(eve::tchebytchev)(n ? dec(n) : zero(as(n)), x);
  }

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , decorated<flx::derivative_<2>(kind_1_type)> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    return flx::derivative(eve::tchebytchev)(n, x);
  }

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , decorated<flx::derivative_<2>(kind_2_type)> const &
                                  , N const &n
                                  , T const &x) noexcept
  {

    auto nn = convert(n, as<element_type_t<T>>());
    auto nnp1 =  inc(nn);
    auto z = ((nnp1*kind_2(tchebytchev)(inc(n), x)-x*kind_2(tchebytchev)(n, x)))/dec(sqr(x));
    auto z1 = nn*nnp1*inc(nnp1)/3;
    return  if_else(abs(x)-one(as(x))< eps(as(x))
                   , eve::if_else(is_gez(x), z1, z1*sign_alternate(n))
                   , z);

  }

}
