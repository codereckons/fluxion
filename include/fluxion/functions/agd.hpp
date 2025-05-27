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
#include <fluxion/functions/atanh.hpp>
#include <fluxion/functions/tan.hpp>

namespace flx
{
  template<typename Options>
  struct agd_t : eve::elementwise_callable<agd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(agd_t, agd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var agd
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
//!      template<flx::concepts::hyperdual_like T> constexprT agd(T z) noexcept;
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
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$\sec(x)\f$
//!     2. \f$\sec(x)\tan(x)\f$
//!     3. \f$\sec(x)(\tan^2(x)+\sec^2(x))\f$
//!     4. \f$\sec(x)\tan(x)(\tan^2(x)+5\sec^2(x))\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/agd.cpp}
//======================================================================================================================
  inline constexpr auto agd = eve::functor<agd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto agd_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::agd(e0(z));
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
        auto [s, c] = eve::sincos(x);
        auto rc  = eve::rec(c);
        auto rc2 = eve::rec(eve::sqr(c));
        ders[1] = rc;
        if constexpr(ord > 1)
        {
          ders[2] =  s*rc2;
          if constexpr(ord > 2)
          {
            ders[3] =  (s*s+1)*rc2*rc;
            if constexpr(ord > 3)
            {
              ders[4] =  s*rc2*(6*rc2-1);
            }
          }
        }
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
//       else if constexpr(flx::order_v<Z> == 4)
//       {
//         return chain(z, ders[0], ders[1], ders[2], ders[3], ders[4]);
//       }
//       else
      {
        return taylor(z, ders);
      }

      //return 2*flx::atanh(flx::tan(z*eve::half(as(e0(z)))));
    }
  }
}
