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


  template<ordered_value N, value T, value U, value V>
  EVE_FORCEINLINE constexpr auto jacobi_(EVE_SUPPORTS(cpu_)
                                     , flx::derivative_type<1> const &
                                     , N const & n
                                     , U const & alpha
                                     , V const & beta
                                     , T const &x
                                     , size_t k) noexcept
  -> indexed_common_value_t<N, U, V, T>
  {
    using f_t = indexed_common_value_t<N, U, V, T>;
    f_t scale(1);
    auto nn(to_<f_t>(n));
    auto apbpn = alpha+beta+nn;
    for(size_t j = 1; j <= k; ++j) scale *= (apbpn+j)/2;
    auto j = jacobi(nn-k, alpha+k, beta+k, x);
    return if_else(k > nn, zero, j*scale);
  }

  template<ordered_value N, value T, value U, value V>
  EVE_FORCEINLINE constexpr auto jacobi_(EVE_SUPPORTS(cpu_)
                                        , flx::derivative_type<1> const &
                                        , N const & n
                                        , U const & alpha
                                        , V const & beta
                                        , T const &x) noexcept
  -> indexed_common_value_t<N, U, V, T>
  {
    using f_t = indexed_common_value_t<N, U, V, T>;
    auto nn(to_<f_t>(n));
    return if_else(is_eqz(n), zero, (alpha + beta + inc(nn))*f_t(0.5)*jacobi(dec(n), inc(alpha), inc(beta), x));
  }

}
