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

  //// cbrt
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto cb = eve::rec(v);
    return Z{cb, eve::rec(3*eve::sqr(cb))*d};
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
    return kumi::tuple{Z{s, d*c}, Z{c, -d*s}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinpicospi_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinpicospi(v);
    auto fac = eve::pi(eve::as(v));
    return kumi::tuple{Z{s, d*c*fac}, Z{c, -d*s*fac}};
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
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinhcosh_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
  }

  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sinh_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto [s, c]= eve::sinhcosh(v);
    return Z{s, d*c};
  }

//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::add_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::add(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = val(z1)+val(z2);
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, v_t(der(z2)));
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)));
//     else                                             return r_t(z, v_t(der(z1))+v_t(der(z2)));
//   }

}
