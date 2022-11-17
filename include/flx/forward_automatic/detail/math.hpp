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

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

// Those functions have a specific derivation specified here
template<> struct flx::has_optimized_derivative<eve::tag::exp_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp2_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp10_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sincos_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sindcosd_>       : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinhcosh_>      : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinpicospi_>    : std::true_type {};

namespace flx::detail
{

  //// exp
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp_, Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto e = eve::exp(v);
    return Z{e, e*d};
  }

  //// exp2
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp2_, Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto e = eve::exp2(v);
    return Z{e, e*eve::log_2(eve::as(v))*d};
  }

  //// exp10
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp10_, Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto e = eve::exp10(v);
    return Z{e, e*eve::log_10(eve::as(v))*d};
  }

  //==============================================================================================
  //  returning tuples
  //==============================================================================================
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sincos_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return kumi::tuple{Z{s, d*c}, Z{c, -d*s}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sinpicospi_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    auto fac = eve::pi(eve::as(v));
    return kumi::tuple{Z{s, d*c*fac}, Z{c, -d*s*fac}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sindcosd_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    auto fac = eve::deginrad(d);
    return kumi::tuple{Z{s, c*fac}, Z{c, -s*fac}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sinhcosh_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
  }

}
