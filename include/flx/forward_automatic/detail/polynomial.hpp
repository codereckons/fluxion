//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <flx/derivative/derivatives.hpp>
#include <flx/forward_automatic/is_derivable.hpp>
#include <flx/forward_automatic/der.hpp>
#include <flx/forward_automatic/val.hpp>

#include <eve/module/polynomial.hpp>

// Those functions have a specific derivation specified here
template<> struct flx::has_optimized_derivative<eve::tag::tchebytchev_>         : std::true_type {};

namespace flx::detail
{

  //// tchebytchev
  template<eve::value N, typename Z>
  EVE_FORCEINLINE  auto
  valder_binary_dispatch( eve::tag::tchebytchev_
                        , N const& n
                        , Z const& z ) noexcept
  {
    using v_t = decltype(eve::tchebytchev(n, val(z)));
    using r_t = as_valder_t<v_t>;
    return r_t{eve::tchebytchev(n, val(z))
               , flx::derivative_2nd(eve::tchebytchev)(n, val(z))*der(z)};
  }

  template<eve::value N, typename Z>
  EVE_FORCEINLINE auto valder_binary_dispatch( eve::tag::tchebytchev_
                                             , eve::kind_1_type const &
                                             , N const& n
                                             , Z const& z ) noexcept
  {
    return tchebytchev(n, z);
  }

  template<eve::value N, typename Z>
  EVE_FORCEINLINE auto valder_binary_dispatch( eve::tag::tchebytchev_
                                             , eve::kind_2_type const &
                                             , N const& n
                                             , Z const& z ) noexcept
  {
    using v_t = decltype(eve::tchebytchev(n, val(z)));
    using r_t = as_valder_t<v_t>;
    return r_t{eve::kind_2_type()(eve::tchebytchev)(n, val(z))
        , eve::tchebytchev(eve::decorated<flx::derivative_<2>(eve::kind_2_type)>(), n, val(z))*der(z)};
  }
}
