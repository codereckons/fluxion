//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>
#include <fluxion/functions/parts.hpp>
#include <eve/module/math.hpp>

namespace flx
{
  template<typename Options>
  struct atanh_t : eve::elementwise_callable<atanh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(atanh_t, atanh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanh
//!   @brief Computes the arc cosine of the argument.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      template<flx::concepts::hyperdual_like T> constexprT atanh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cosine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanh.cpp}
//======================================================================================================================
  inline constexpr auto atanh = eve::functor<atanh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto atanh_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::atanh(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto comp_ders = [&ders](auto  x){
        constexpr auto ord = flx::order_v<Z>;
        auto d1 =  eve::rec(eve::oneminus(eve::sqr(x)));
        ders[1] = d1;
        if constexpr(ord == 1)   return;
        ders[2] = 2*x*eve::sqr(d1);
        if constexpr(ord == 2)   return;
        ders[3] = 2*eve::inc(3*eve::sqr(x))*eve::sqr(d1*d1)*d1;
        if constexpr(ord == 3)   return;
        ders[4] = 24*x*(eve::inc(eve::sqr(x)))*eve::sqr(eve::sqr(d1));
        return;
      };
      comp_ders(e0(z));
      if constexpr(flx::order_v<Z> == 1)
      {
        return Z(ders[0], ders[1]*e1(z));
      }
      else if constexpr(flx::order_v<Z> == 2)
      {
        return chain(z, ders[0], ders[1], ders[2]);
      }
      else if constexpr(flx::order_v<Z> == 3)
      {
        return chain(z, ders[0], ders[1], ders[2], ders[3]);
      }
      else if constexpr(flx::order_v<Z> == 4)
      {
        return chain(z, ders[0], ders[1], ders[2], ders[3], ders[4]);
      }
      else
      {
        return taylor(z, ders);
      }
      //return eve::half(eve::as(val))*flx::log(flx::inc(z)/flx::oneminus(z));
    }
  }
}
