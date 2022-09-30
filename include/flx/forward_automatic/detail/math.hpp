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
  
  template<typename Z>
  EVE_FORCEINLINE  auto valder_unary_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
  {
    auto [v, d] = z;
    auto cb = eve::rec(v);
    return Z{cb, eve::rec(3*eve::sqr(cb))*d};
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
