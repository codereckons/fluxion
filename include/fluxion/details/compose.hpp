//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/abi.hpp>
#include <array>

namespace flx::_
{

  template < typename T> FLX_FORCEINLINE T taylor(T const & z, auto ders) noexcept
  {
    using b_t = flx::as_base_type_t<T>;
    auto pz = flx::pure(z);
    auto p1 = pz;
    T p(ders[0]);
    b_t n(1);
    for(unsigned short i=1; i <= flx::order_v<T>; ++i)
    {
      n *= i;
      p += p1*ders[i]/n;
      p1 *= pz;
    }
    return p;
  }

  template < typename T> FLX_FORCEINLINE T
  chain(T const & z
       , flx::as_base_type_t<T> val
       , flx::as_base_type_t<T> der
       ) noexcept
  {
    return flx::as_hyperdual_t<T>(val, der*e1(z));
  }

  template < typename T> FLX_FORCEINLINE T
  chain(T const & z
       , flx::as_base_type_t<T> val
       , flx::as_base_type_t<T> der
       , flx::as_base_type_t<T> acc
       ) noexcept
  {
    return flx::as_hyperdual_t<T>
      (val, der*e1(z), der*e2(z)
      , (der*e12(z)+acc*e1(z)*e2(z)));
  }

  template < typename T> FLX_FORCEINLINE T
  chain(T const & z
       , flx::as_base_type_t<T> val
       , flx::as_base_type_t<T> der
       , flx::as_base_type_t<T> acc
       , flx::as_base_type_t<T> jrk
       ) noexcept
  {
    return flx::as_hyperdual_t<T>
      (val
      , der*e1(z)
      , der*e2(z)
      , der*e12(z)+acc*e1(z)*e2(z)
      , der*e3(z)
      , der*e13(z)+acc*e1(z)*e3(z)
      , der*e23(z)+acc*e2(z)*e3(z)
      , der*e123(z)+acc*(e1(z)*e23(z)+e3(z)*e12(z)+e2(z)*e13(z))+jrk*e1(z)*e2(z)*e3(z));
  }

  template < typename T> FLX_FORCEINLINE T
  chain(T const & z
       , flx::as_base_type_t<T> val
       , flx::as_base_type_t<T> der
       , flx::as_base_type_t<T> acc
       , flx::as_base_type_t<T> jrk
       , flx::as_base_type_t<T> snp
       ) noexcept
  {
    return flx::as_hyperdual_t<T>
      (val
      , der*e1(z)//e1
      , der*e2(z)//e2
      , der*e12(z)+acc*e1(z)*e2(z)//e12

      , der*e3(z)//e3
      , der*e13(z)+acc*e1(z)*e3(z)//e13
      , der*e23(z)+acc*e2(z)*e3(z)//e23
      , der*e123(z)+ acc*(e1(z)*e23(z)+e3(z)*e12(z)+ e2(z)*e13(z))+jrk*e1(z)*e2(z)*e3(z)//e123

      , der*e4(z)//e4
      , der*e14(z)+acc*e1(z)*e4(z)//e14
      , der*e24(z)+acc*e2(z)*e4(z)//e24

      , der*e124(z)+ acc*(e1(z)*e24(z)+e4(z)*e12(z)+ e2(z)*e14(z))+jrk*e1(z)*e2(z)*e4(z)
      , der*e34(z)+acc*e3(z)*e4(z)
      , der*e134(z)+ acc*(e1(z)*e34(z)+e4(z)*e13(z)+ e3(z)*e14(z))+jrk*e1(z)*e3(z)*e4(z)
      , der*e234(z)+ acc*(e2(z)*e34(z)+e4(z)*e23(z)+ e3(z)*e24(z))+jrk*e2(z)*e3(z)*e4(z)
      , der*e1234(z)+ acc*(e12(z)*e34(z)+e13(z)*e24(z)+ e14(z)*e23(z)) +jrk*(e1(z)*e234(z)+e2(z)*e134(z)+e3(z)*e124(z)+e4(z)*e123(z))
       +der*(e1(z)*e2(z)*e34(z)+e1(z)*e3(z)*e24(z)+ e1(z)*e4(z)*e23(z)+ e2(z)*e3(z)*e14(z)+ e2(z)*e4(z)*e13(z)+  e3(z)*e4(z)*e12(z))
      +snp*e1(z)*e2(z)*e3(z)*e4(z)
      );
  }


  //evaluate using prepared derivatives
  template <int order = -1, concepts::hyperdual Z> FLX_FORCEINLINE
  constexpr auto evaluate(auto const & ders, Z const & z) noexcept
  {
    constexpr int ord = order == -1 ? flx::order_v<Z> : order;
    if constexpr(ord == 1)
    {
      return Z(ders[0], ders[1]*e1(z));
    }
    else if constexpr(ord == 2)
    {
      return chain(z, ders[0], ders[1], ders[2]);
    }
    else if constexpr(ord == 3)
    {
      return chain(z, ders[0], ders[1], ders[2], ders[3]);
    }
//       else if constexpr(flx::order_v<Z> == 4)
//       {
//         return chain(z, ders[0], ders[1], ders[2], ders[3], ders[4]);
//       }
    else
    {
      return taylor(z, ders);
    }

  }
}
