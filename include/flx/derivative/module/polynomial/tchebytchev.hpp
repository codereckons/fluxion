//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#pragma once
#include <flx/derivative/derivative.hpp>
#include <eve/module/math.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{
  template<auto I, value N, floating_value T>
  EVE_FORCEINLINE auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                   , flx::derivative_type<I> const &
                                   , N const &n
                                   , T const &x) noexcept
  {
    EVE_ASSERT(eve::all(eve::is_flint(n)), "some tchebytchev orders are not flint");
//    using r_t = decltype(eve::tchebytchev(n, x));
    if constexpr(I == 2)
    {
      auto nn = convert(n, as<element_type_t<T>>());
      if constexpr(eve::scalar_value<N>)
      {
        return nn*kind_2(eve::tchebytchev)(n ? dec(n) : zero(as(n)), x);
      }
      else
      {
        return nn*kind_2(eve::tchebytchev)(if_else(eve::is_nez(nn), dec(n), zero), x);
      }
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

  template<auto I, value N, floating_value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , decorated<flx::derivative_<I>(kind_1_type)> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    return flx::derivative_nth<I>(eve::tchebytchev)(n, x);
  }

  template<auto I, value N, floating_value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                             , decorated<flx::derivative_<I>(kind_2_type)> const &
                                             , N const &n
                                             , T const &x) noexcept
  {
    EVE_ASSERT(eve::all(eve::is_flint(n)), "some tchebytchev orders are not flint");
    if constexpr(I == 2)
    {
      auto nn = convert(n, as<element_type_t<T>>());  
      auto nnp1 =  eve::inc(nn);
      auto z = ((nnp1*eve::kind_2(eve::tchebytchev)(inc(n), x)-x*eve::kind_2(eve::tchebytchev)(n, x)))/eve::dec(eve::sqr(x));
      auto z1 = nn*nnp1*eve::inc(nnp1)/3;
      return  eve::if_else(eve::abs(x)-one(as(x))< eve::eps(as(x))
                     , eve::if_else(eve::is_gez(x), z1, z1*eve::sign_alternate(nn))
                     , z);
    }
    else
    {
      EVE_ASSERT( I == 2, "tchebytchev derivative is only implemented relative to second parameter");
      return nan(as<T>());
    }
  }

}
