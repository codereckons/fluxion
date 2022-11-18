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
template<> struct flx::has_optimized_derivative<eve::tag::atan2_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::atan2d_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::atan2pi_>       : std::true_type {};

template<> struct flx::has_optimized_derivative<eve::tag::exp_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp2_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp10_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sincos_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sindcosd_>       : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinhcosh_>      : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinpicospi_>    : std::true_type {};

namespace flx::detail
{

  /// atan2
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::atan2_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::atan2(val(z1), val(z2)));
    using elt_t = eve::element_type_t<v_t>;
    using r_t = flx::as_valder_t<v_t>;
    auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
    auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
    auto  invden = eve::rec(eve::sum_of_prod(v1, v1, v2, v2));
    auto  at2 = eve::atan2(v1, v2);
    if constexpr(! eve::like<Z1, valder<elt_t>>)
      return r_t(at2, invden*v1*d2);
    else if constexpr(! eve::like<Z2, valder<elt_t>>)
      return r_t(at2, invden*v2*d1);
    else
      return r_t{at2, invden*eve::sum_of_prod(v1, d2, v2, d1)};
  }

  /// atan2d
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::atan2d_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::atan2d(val(z1), val(z2)));
    using r_t = flx::as_valder_t<v_t>;
    using elt_t = eve::element_type_t<v_t>;
    auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
    auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
    auto  invden = eve::radindeg(eve::rec(eve::sum_of_prod(v1, v1, v2, v2)));
    auto  at2 = eve::atan2d(v1, v2);
    if constexpr(! eve::like<Z1, valder<elt_t>>)
      return r_t(at2, invden*v1*d2);
    else if constexpr(! eve::like<Z2, valder<elt_t>>)
      return r_t(at2, invden*v2*d1);
    else
      return r_t{eve::atan2d(v1, v2), invden*eve::sum_of_prod(v1, d2, v2, d1)};
  }

  /// atan2pi
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::atan2pi_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::atan2pi(val(z1), val(z2)));
    using r_t = flx::as_valder_t<v_t>;
    using elt_t = eve::element_type_t<v_t>;
    auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
    auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
    auto  invden = eve::radinpi(eve::rec(eve::sum_of_prod(v1, v1, v2, v2)));
    auto  at2 = eve::atan2pi(v1, v2);
    if constexpr(! eve::like<Z1, valder<elt_t>>)
      return r_t(at2, invden*v1*d2);
    else if constexpr(! eve::like<Z2, valder<elt_t>>)
      return r_t(at2, invden*v2*d1);
    else
      return r_t{eve::atan2d(v1, v2), invden*eve::sum_of_prod(v1, d2, v2, d1)};
  }

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
