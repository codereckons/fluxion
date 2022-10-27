//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

namespace flx::detail
{

  /// atan2xxx
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
    auto cb = eve::rec(v);
    return Z{cb, eve::rec(3*eve::sqr(cb))*d};
  }

  //// cosxxx
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cos_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return Z{c, -d*s};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cosd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    return Z{c, -d*eve::deginrad(s)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cosh_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return Z{c, d*s};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cospi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    return Z{c, -d*s*eve::pi(eve::as(v))};
  }

  //// cscxxx
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::csc_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::csc(v);
    return Z{cs, -d*cs*eve::cot(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cscd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::cscd(v);
    return Z{cs, -d*eve::deginrad(cs)*eve::cotd(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::csch_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::csch(v);
    return Z{cs, -d*cs*eve::coth(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::cscpi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto cs = eve::cscpi(v);
    return Z{cs, -d*cs*eve::cotpi(v)*eve::pi(eve::as(v))};
  }

  //// nthroot
  template<typename Z>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::nthroot_
                                              , Z  const& z
                                              , eve::value auto const& n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)),  "n is not flint");
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

  //// secxxx
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::sec_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::sec(v);
    return Z{se, d*se*eve::tan(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::secd_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::secd(v);
    return Z{se, d*eve::deginrad(se)*eve::tand(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::sech_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::sech(v);
    return Z{se, -d*se*eve::tanh(v)};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::secpi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto se = eve::secpi(v);
    return Z{se, d*se*eve::tanpi(v)*eve::pi(eve::as(v))};
  }

  //// sinxxx
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sin_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);
    return Z{s, d*c};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sincos_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sincos(v);

    return kumi::tuple{Z{s, c}, Z{c, -s}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinpi_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    return Z{s, d*c*eve::pi(eve::as(v))};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sindcosd_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    auto fac = eve::deginrad(d);
    return kumi::tuple{Z{s, c*fac}, Z{c, -s*fac}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sind_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sindcosd(v);
    return Z{s, d*eve::deginrad(c)};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinh_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return Z{s, d*c};
  }

  ////tanxxx
  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::tan_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto t = eve::tan(v);
    return Z{t, d*eve::inc(eve::sqr(t))};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::tanpi_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto t = eve::tanpi(v);
    return Z{t, d*eve::inc(eve::sqr(t))*eve::pi(eve::as(v))};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::tand_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto t = eve::tand(v);
    return Z{t, eve::deginrad(d)*eve::inc(eve::sqr(t))};
  }

  template<typename Z>
  EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::tanh_
                                            , Z const& z ) noexcept
  {
    auto [v, d] = z;
    auto t = eve::tanh(v);
    return Z{t, eve::oneminus(eve::sqr(t))*d};
  }

//   template<typename Z>
//   EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::log_
//                                             , Z const& z ) noexcept
//   {
//     auto [v, d] = z;
//     auto t = eve::log(v);
//     return Z{t, eve::rec(v)*d};
//  }
}
