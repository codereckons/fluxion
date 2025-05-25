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
  struct asin_t : eve::elementwise_callable<asin_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asin_t, asin_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asin
//!   @brief Computes the arc sine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asin(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc sine of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$\frac{1}{\sqrt(1-x^2)}\f$
//!     2. \f$\frac{x}{(1-x^2)^{3/2}}\f$
//!     3. \f$\frac{2 x^2+1}{(1 - x^2)^{5/2}}\f$
//!     4. \f$\frac{6x^3+9x}{(1 - x^2)^{7/2}}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asin.cpp}
//======================================================================================================================
  inline constexpr auto asin = eve::functor<asin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asin_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::asin(e0(z));
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
        auto x2 = eve::sqr(x);
        auto r = eve::rec(eve::oneminus(x2));
        ders[1] = eve::rsqrt(r);
        if constexpr(ord == 1) return;
        else
        {
          for(unsigned short i=2; i <= ord ; ++i)
          {
            ders[i] = ders[i-1]*r;
          }
          ders[2] *= x;
          if constexpr(ord == 2)   return;
          ders[3] *= (eve::inc(2*x2));
          if constexpr(ord == 3)   return;
          ders[4] *= (6*x2+9)*x;
          return;
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
