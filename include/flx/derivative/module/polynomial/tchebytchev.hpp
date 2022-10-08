//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<auto I, scalar_value N, floating_value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , flx::derivative_type<I> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    if constexpr(I == 2)
    {
      auto nn = convert(n, as<element_type_t<T>>());
      return nn*kind_2(eve::tchebytchev)(n ? dec(n) : zero(as(n)), x);
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

  template<auto I, scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , decorated<flx::derivative_<I>(kind_1_type)> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    if constexpr(I == 2)
    {
      return flx::derivative_2nd(eve::tchebytchev)(n, x);
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

  template<auto I, value N, floating_value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , flx::derivative_<I> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    if constexpr(I == 2)
    {
      return flx::derivative_2nd(eve::tchebytchev)(n, x);
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

  template<auto I, scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , decorated<flx::derivative_<I>(kind_2_type)> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    if constexpr(I == 2)
    {
      auto nn = convert(n, as<element_type_t<T>>());
      auto nnp1 =  inc(nn);
      auto z = ((nnp1*kind_2(tchebytchev)(inc(n), x)-x*kind_2(tchebytchev)(n, x)))/dec(sqr(x));
      auto z1 = nn*nnp1*inc(nnp1)/3;
      return  if_else(abs(x)-one(as(x))< eps(as(x))
                     , if_else(is_gez(x), z1, z1*alternate_sign(n))
                     , z);
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

}
