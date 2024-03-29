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

// Those functions have a specific derivation specified here
template<> struct flx::has_optimized_derivative<eve::tag::dist_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::exponent_>    : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::if_else_>     : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::ifnot_else_>  : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::ldexp_>       : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::mantissa_>    : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::modf_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::rec_>         : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::rsqrt_>       : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::sqrt_>        : std::true_type {};
template<> struct flx::has_optimized_derivative<eve::tag::ulpdist_>     : std::true_type {};

namespace flx::detail
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// add, mul, sub, div
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  valder_binary_dispatch(eve::tag::add_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 + z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  valder_binary_dispatch(eve::tag::sub_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 - z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  valder_binary_dispatch(eve::tag::mul_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 * z2;
  }

  template<typename Z1, typename Z2>
  EVE_FORCEINLINE auto
  valder_binary_dispatch(eve::tag::div_, Z1 const& z1, Z2 const& z2) noexcept
  {
    return z1 / z2;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// other optimizations
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  //// dist
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::dist_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::dist(val(z1), val(z2)));
    using r_t = flx::as_valder_t<v_t>;
    auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
    auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
    auto  s = eve::sign(v1-v2);
    return r_t{eve::dist(v1, v2), s*(d1-d2)};
  }

  //// exponent
  template<typename Z>
  EVE_FORCEINLINE auto
  valder_unary_dispatch(eve::tag::exponent_, Z const& z) noexcept
  {
    auto v = eve::convert(eve::exponent(val(z)), eve::as<eve::element_type_t<decltype(val(z))>>());
    return Z{v, eve::zero(eve::as(val(z)))};
  }

  //// fmod
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::fmod_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    return eve::rem(z1, z2);
  }

  //// if_else
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto
  valder_ternary_dispatch ( eve::tag::if_else_
                       , auto const & vc
                       , Z1 const & a
                       , Z2 const & b
                       ) noexcept
  {
    using v_t = decltype(eve::if_else(vc, val(a), val(b)));
    using e_t = eve::element_type_t<v_t>;
    using r_t = flx::as_valder_t<v_t>;
    auto r = eve::if_else(vc, val(a), val(b));
    if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(r, eve::if_else(vc, eve::zero, der(b)));
    else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(r, eve::if_else(vc, der(a), eve::zero));
    else                                             return r_t{r, eve::if_else(vc, der(a), der(b))};
  }


  //// ifnot_else
  template< typename Z1,  typename Z2>
  EVE_FORCEINLINE  auto
  valder_ternary_dispatch ( eve::tag::ifnot_else_
                          , auto const & c
                          , Z1 const & a
                          , Z2 const & b
                          ) noexcept
  {
    return eve::if_else(c, b, a);
  }



  //     template < eve::like < valder> Z2, eve::generator < typename Z2::value_type> Constant>
  //     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
  //                                                , auto const & vc
  //                                                , Constant const& a
  //                                                , Z2 const& b ) noexcept
  //     {
  //       auto vb = val(b); auto db = der(b);
  //       using v_t = decltype(eve::if_else(vc, a, vb));
  //       using r_t = as_valder_t<v_t>;
  //       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
  //     }

  //     template < eve::like < valder> Z1, eve::generator < typename Z1::value_type> Constant>
  //     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
  //                                                , auto const & vc
  //                                                , Z1 const& b
  //                                                , Constant const& a

  //                                                ) noexcept
  //     {
  //       auto vb = val(b); auto db = der(b);
  //       using v_t = decltype(eve::if_else(vc, a, vb));
  //       using r_t = as_valder_t<v_t>;
  //       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
  //     }

  //// ldexp
  template<typename Z, eve::value N>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::ldexp_
                                              , Z const& z,  N const& n) noexcept
  {
    auto nn = eve::convert(n, eve::as<eve::element_type_t<decltype(val(z))>>());
    return Z{eve::ldexp(val(z), nn), eve::ldexp(eve::one(eve::as(val(z))), nn)*der(z)};
  }

  //// mantissa
  template<typename Z>
  EVE_FORCEINLINE auto
  valder_unary_dispatch(eve::tag::mantissa_, Z const& z) noexcept
  {
    return Z{eve::mantissa(val(z)), eve::ldexp(eve::sign(val(z)), -eve::exponent(val(z)))};
  }


  //// modf
  template<typename Z>
  EVE_FORCEINLINE  auto
  valder_unary_dispatch(eve::tag::modf_, Z const& z ) noexcept
  {
    auto f = eve::frac(val(z));
    auto t = eve::trunc(val(z));

    return kumi::tuple{  Z{f, eve::one(eve::as(f)) }
                       , Z{t, eve::zero(eve::as(t))}
                               };
  }

  //// rec
  template<typename Z>
  EVE_FORCEINLINE auto
  valder_unary_dispatch(eve::tag::rec_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto inv    = eve::rec(v);
    return Z {inv, -eve::sqr(inv) * d};
  }

  //// rsqrt
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::rsqrt_
                                              , Z const& z) noexcept
  {
    auto [v, d] = z;
    auto rs = eve::rsqrt(v);
    return Z{rs, d*eve::mhalf(eve::as(v))*rs*eve::rec(v)};
  }

  //// sqrt
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sqrt_
                                              , Z const& z) noexcept
  {
    auto [v, d] = z;
    auto sqrtv = eve::sqrt(v);
    return Z{sqrtv, d/(2*sqrtv)};
  }


  //// ulpdist between two valders return a floating_value DOESNOT comote any derivative
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::ulpdist_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    return eve::max( eve::ulpdist(val(z1), val(z2))
                   , eve::ulpdist(der(z1), der(z2)));
  }

 }

// Those functions can't be derived
template<> struct flx::is_derivable<eve::tag::all_>                   : std::false_type {};
template<> struct flx::is_derivable<eve::tag::any_>                   : std::false_type {};
template<> struct flx::is_derivable<eve::tag::count_true_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::epsilon_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::gather_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::hi_>                    : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_denormal_>           : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_equal_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_equal_>          : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_less_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_less_equal_>         : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_lessgreater_>        : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_greater_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_greater_equal_>      : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_ordered_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_unordered_>          : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_less_>           : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_less_equal_>     : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_greater_>        : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_greater_equal_>  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_eqz_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_even_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_infinite_>           : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_finite_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_flint_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_lez_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_ltz_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_gez_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_gtz_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_nez_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_negative_>           : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_nlez_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_nltz_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_ngez_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_ngtz_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_normal_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_denormal_>       : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_finite_>         : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_flint_>          : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_infinite_>       : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_nan_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_not_nan_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_odd_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_positive_>           : std::false_type {};
template<> struct flx::is_derivable<eve::tag::is_pow2_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::lo_>                    : std::false_type {};
template<> struct flx::is_derivable<eve::tag::lohi_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::lookup_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::maximum_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::minimum_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_and_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_andnot_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_cast_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_ceil_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_floor_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_mask_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_notand_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_not_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_notor_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bitofsign_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_or_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_ornot_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_select_>            : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_shr_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_width_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::bit_xor_>               : std::false_type {};
template<> struct flx::is_derivable<eve::tag::next_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::nextafter_>             : std::false_type {};
template<> struct flx::is_derivable<eve::tag::none_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::popcount_>              : std::false_type {};
template<> struct flx::is_derivable<eve::tag::prev_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::reduce_>                : std::false_type {};
template<> struct flx::is_derivable<eve::tag::rotl_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::rotr_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::rshl_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::rshr_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::scan_>                  : std::false_type {};
template<> struct flx::is_derivable<eve::tag::shl_>                   : std::false_type {};
template<> struct flx::is_derivable<eve::tag::shr_>                   : std::false_type {};
template<> struct flx::is_derivable<eve::tag::significants_>          : std::false_type {};
