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


  template<auto I, real_value N, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE constexpr T jacobi_(EVE_SUPPORTS(cpu_)
                                     , flx::derivative_type<I> const &
                                     , N const & n
                                     , U const & alpha
                                     , V const & beta
                                     , T const &x
                                     , size_t k) noexcept
  {
    using f_t = common_compatible_t<T, U, V>;
    if constexpr(I == 4)
    {
      f_t scale(1);
      auto nn(to_<f_t>(n));
      auto apbpn = alpha+beta+nn;
      for(size_t j = 1; j <= k; ++j) scale *= (apbpn+j)/2;
      auto j = jacobi(nn-k, alpha+k, beta+k, x);
      return if_else(k > nn, zero, j*scale);
    }
    else
    {
      EVE_ASSERT( I == 4, "jacobi derivative is only implemented relative to 4th parameter");
      return nan(as<f_t>());
    }
  }

  template<auto I, real_value N, floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE constexpr auto jacobi_(EVE_SUPPORTS(cpu_)
                                        , flx::derivative_type<I> const &
                                        , N const & n
                                        , U const & alpha
                                        , V const & beta
                                        , T const &x) noexcept
  {
    using f_t = common_compatible_t<T, U, V>;
    if constexpr(I == 4)
    {
    auto nn(to_<f_t>(n));
    return if_else(is_eqz(n), zero, (alpha + beta + inc(nn))*f_t(0.5)*jacobi(dec(n), inc(alpha), inc(beta), x));
  }
    else
    {
      EVE_ASSERT( I == 4, "jacobi derivative is only implemented relative to 4th parameter");
      return nan(as<f_t>());
    }

  }
}
