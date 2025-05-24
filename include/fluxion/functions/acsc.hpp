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
#include <eve/module/math.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acsc_t : eve::elementwise_callable<acsc_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acsc_t, acsc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsc
//!   @brief Computes the arc cosecant of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acsc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cosecant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$\frac{-1}{ x^2\sqrt{1-1/x^2}}\f$
//!     2. \f$\frac{2x2-1}{x^3(x^2-1)\sqrt{1-1/x^2}}\f$
//!     3. \f$\frac{-6x^4+5x^2-2}{x^3(x^2-1)^2\sqrt{1-1/x^2}}\f$
//!     4. \f$-\frac{3(8x^6-8x^4+7x^2-2}{x^5(x^2-1^3)\sqrt{1-1/x^2}}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acsc.cpp}
//======================================================================================================================
  inline constexpr auto acsc = eve::functor<acsc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acsc_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::acsc(e0(z));
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
        auto  x2 = eve::sqr(x);
        auto rx2 = eve::rec(x2);
        auto coef = eve::rsqrt(oneminus(rx2));
        ders[1] = -coef;
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = coef*rx2*(2*x2-1)/(x2-1); ;
          if constexpr(ord == 2)   return;
          else
          {
            ders[3] = coef*eve::sqr(rx2)*eve::horner(x2, b_t(-2), b_t(5), b_t(-6))/eve::sqr(x2-1);
            if constexpr(ord == 3)   return;
            else
            {
              ders[4] = coef*eve::sqr(rx2)*3**eve::horner(x2,b_t(-2),b_t(7),b_t(-8),b_t(8))/(x*eve::sqr(x2-1)*(x2-1));
              return;
            }
          }
        }
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
}
