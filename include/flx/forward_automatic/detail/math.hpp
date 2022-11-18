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
template<> struct flx::has_optimized_derivative<eve::tag::cbrt_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cos_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cosd_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cosh_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cospi_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::csc_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cscd_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::csch_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::cscpi_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp2_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exp10_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::nthroot_>       : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::pow_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sec_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::secd_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sech_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::secpi_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sin_>           : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sincos_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sind_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sindcosd_>      : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinh_>          : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinhcosh_>      : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sinpi_>         : std::true_type {};
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


  //// cbrt
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto cb = eve::cbrt(v);
    return Z{cb, eve::rec(3*eve::sqr(cb))*d};
  }

  //// cos
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cos_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return Z{c, -d*s};
  }

  //// cosd
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cosd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    return Z{c, -d*eve::deginrad(s)};
  }

  //// cosh
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cosh_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return Z{c, d*s};
  }

  //// cospi
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cospi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    return Z{c, -d*s*eve::pi(eve::as(v))};
  }


  //// csc
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::csc_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::csc(v);
    return Z{cs, -d*cs*eve::cot(v)};
  }

  //// cscd
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cscd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::cscd(v);
    return Z{cs, -d*eve::deginrad(cs)*eve::cotd(v)};
  }

  //// csch
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::csch_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::csch(v);
    return Z{cs, -d*cs*eve::coth(v)};
  }

  //// cscpi
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cscpi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::cscpi(v);
    return Z{cs, -d*cs*eve::cotpi(v)*eve::pi(eve::as(v))};
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

  //// nthroot
  template<typename Z>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::nthroot_
                                              , Z  const& z
                                              , eve::value auto const& n) noexcept
  {
    EVE_ASSERT(eve::all(eve::is_flint(n)),  "n is not flint");
    auto v1 = val(z); auto d1 = der(z);
    auto rn = eve::nthroot(v1, n);
    using v_t =  decltype(rn);
    using elt_t = eve::element_type_t<v_t>;
    auto fn = eve::rec(eve::convert(n, eve::as<elt_t>())*v1);
    using r_t = as_valder_t<v_t>;
    return r_t{rn, rn*fn*d1};
  }

  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::pow_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::pow(val(z1), val(z2)));
    using r_t = as_valder_t<v_t>;
    using elt_t = eve::element_type_t<v_t>;
    if constexpr(! eve::like<Z1, valder<elt_t>>)
    {
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto p = eve::pow(z1, v2);
      return r_t{p, eve::log(z1)*p*d2};
    }
    else if constexpr(! eve::like<Z2, valder<elt_t>>)
    {
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto  p = eve::pow(v1, z2);
      return r_t{p, p*(z2/v1)*d1};
    }
    else
    {
      auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
      auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
      auto  puv = eve::pow(v1, v2);
      return r_t{puv, puv*eve::sum_of_prod(v2/v1, d1, eve::log(v1), d2)};
    }
  }


  //// sec
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::sec_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::sec(v);
    return Z{se, d*se*eve::tan(v)};
  }

  //// secd
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::secd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::secd(v);
    return Z{se, d*eve::deginrad(se)*eve::tand(v)};
  }

  //// sech
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::sech_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::sech(v);
    return Z{se, -d*se*eve::tanh(v)};
  }

  //// secpi
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::secpi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::secpi(v);
    return Z{se, d*se*eve::tanpi(v)*eve::pi(eve::as(v))};
  }

  //// sin
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sin_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return Z{s, d*c};
  }

  //// sincos
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sincos_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return kumi::tuple{Z{s, d*c}, Z{c, -d*s}};
  }

  //// sind
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sind_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    return Z{s, d*eve::deginrad(c)};
  }

  //// sindcosd
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sindcosd_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    auto fac = eve::deginrad(d);
    return kumi::tuple{Z{s, c*fac}, Z{c, -s*fac}};
  }

  //// sinh
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinh_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return Z{s, d*c};
  }


  //// sinhcosh
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sinhcosh_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
  }

  //// sinpi
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinpi_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    return Z{s, d*c*eve::pi(eve::as(v))};
  }

  //// sinpicospi
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch( eve::tag::sinpicospi_
                                             , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    auto fac = eve::pi(eve::as(v));
    return kumi::tuple{Z{s, d*c*fac}, Z{c, -d*s*fac}};
  }


}
