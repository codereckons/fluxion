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
      , der*e1(z)
      , der*e2(z)
      , der*e12(z)+acc*e1(z)*e2(z)
      , der*e3(z)
      , der*e13(z)+acc*e1(z)*e3(z)
      , der*e23(z)+acc*e2(z)*e3(z)
      , der*e123(z)+ acc*(e1(z)*e23(z)+e3(z)*e12(z)+ e2(z)*e13(z))+jrk*e1(z)*e2(z)*e3(z)
      , der*e4(z)
      , der*e14(z)+acc*e1(z)*e4(z)
      , der*e24(z)+acc*e2(z)*e4(z)
      , der*e34(z)+acc*e3(z)*e4(z)
      , der*e124(z)+ acc*(e1(z)*e24(z)+e4(z)*e12(z)+ e2(z)*e14(z))+jrk*e1(z)*e2(z)*e4(z)
      , der*e134(z)+ acc*(e1(z)*e34(z)+e4(z)*e13(z)+ e3(z)*e14(z))+jrk*e1(z)*e3(z)*e4(z)
      , der*e234(z)+ acc*(e2(z)*e34(z)+e4(z)*e23(z)+ e3(z)*e24(z))+jrk*e2(z)*e3(z)*e4(z)
      , der*e1234(z)+ acc*(e12(z)*e34(z)+e13(z)*e24(z)+ e14(z)*e23(z))+jrk*(e1(z)*e234(z)+e2(z)*e134(z)+e3(z)*e124(z)+e4(z)*e123(z))+snp*e1(z)*e2(z)*e3(z)*e4(z)
      );
  }

}
