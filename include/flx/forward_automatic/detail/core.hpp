//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/module/core.hpp>
#include <flx/derivative/derivatives.hpp>

namespace flx::detail
{
  //// rec
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::rec_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto inv = eve::rec(v);
    return Z{inv, -eve::sqr(inv)*d};
  }

  //// add
  template < typename Z1,  typename Z2>
  EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::add_
                                              , Z1 const & z1
                                              , Z2 const & z2
                                              ) noexcept
  {
    using v_t = decltype(eve::add(val(z1), val(z2)));
    using e_t = eve::element_type_t<v_t>;
    using r_t = flx::as_valder_t<v_t>;
    auto z = val(z1)+val(z2);
    if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, v_t(der(z2)));
    else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)));
    else                                             return r_t(z, v_t(der(z1))+v_t(der(z2)));
  }

//   //// dist
//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::dist_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::dist(val(z1), val(z2)));
//     using r_t = flx::as_valder_t<v_t>;
//     auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
//     auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
//     auto  s = eve::sign(v1-v2);
//     return r_t{eve::dist(v1, v2), s*(d1-d2)};
//   }

//   //// div
//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::div_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::div(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = val(z1)/val(z2);
//     auto invvz2 = eve::rec(eve::sqr(val(z2)));
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, -v_t(z1)*v_t(der(z2))*invvz2);
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)/val(z2)));
//     else {
//       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
//       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
//       auto dr = eve::diff_of_prod(v2, d1, v1, d2)*invvz2;
//       return r_t(z, dr);
//     }
//   }

//   //// expxxx
//   template<typename Z>
//   EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp_, Z const& z ) noexcept
//   {
//     auto [v, d] = z;
//     auto e = eve::exp(v);
//     return Z{e, e*d};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp2_, Z const& z ) noexcept
//   {
//     auto [v, d] = z;
//     auto e = eve::exp2(v);
//     return Z{e, e*eve::log_2(eve::as(v))*d};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto valder_unary_dispatch( eve::tag::exp10_, Z const& z ) noexcept
//   {
//     auto [v, d] = z;
//     auto e = eve::exp10(v);
//     return Z{e, e*eve::log_10(eve::as(v))*d};
//   }

//   //// mul
//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::mul_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::mul(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = val(z1)*val(z2);
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, v_t(z1)*v_t(der(z2)));
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(z2)*v_t(der(z1)));
//     else {
//       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
//       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
//       auto dr = eve::sum_of_prod(v1, d2, v2, d1);
//       return r_t(z, dr);
//     }
//   }


//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::rem_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::rem(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = eve::rem(val(z1), val(z2));
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, -eve::trunc(v_t(val(z1))/v_t(val(z2))*v_t(der(z2))));
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)));
//     else
//     {
//       return r_t(z, eve::fsm( v_t(der(z1))
//                             , eve::trunc( v_t(val(z1))/v_t(val(z2)))
//                             , v_t(der(z2))
//                             )
//                 );
//     }
//   }

//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::fmod_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::rem(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = eve::pedantic(eve::rem)(val(z1), val(z2));
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, -eve::trunc(v_t(val(z1))/v_t(val(z2))*v_t(der(z2))));
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)));
//     else
//     {
//       return r_t(z, eve::fsm( v_t(der(z1))
//                             , eve::trunc( v_t(val(z1))/v_t(val(z2)))
//                             , v_t(der(z2))
//                             )
//                 );
//     }
//   }

//   //// rsqrt
//   template<typename Z>
//   EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::rsqrt_
//                                               , Z const& z) noexcept
//   {
//     auto [v, d] = z;
//     auto rs = eve::rsqrt(v);
//     return Z{rs, d*eve::mhalf(eve::as(v))*rs*eve::rec(v)};
//   }

//   //// sub
//   template < typename Z1,  typename Z2>
//   EVE_FORCEINLINE auto valder_binary_dispatch ( eve::tag::sub_
//                                               , Z1 const & z1
//                                               , Z2 const & z2
//                                               ) noexcept
//   {
//     using v_t = decltype(eve::sub(val(z1), val(z2)));
//     using e_t = eve::element_type_t<v_t>;
//     using r_t = flx::as_valder_t<v_t>;
//     auto z = val(z1)-val(z2);
//     if constexpr(!eve::like < Z1, valder<e_t>>)      return r_t(z, -v_t(der(z2)));
//     else if constexpr(!eve::like < Z2, valder<e_t>>) return r_t(z, v_t(der(z1)));
//     else                                             return r_t(z, v_t(der(z1))-v_t(der(z2)));
//   }

//   template<typename Z>
//   EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::sqrt_
//                                               , Z const& z) noexcept
//   {
//     auto [v, d] = z;
//     auto sqrtv = eve::sqrt(v);
//     return Z{sqrtv, d/(2*sqrtv)};
//   }


}
