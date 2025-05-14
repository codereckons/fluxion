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
  struct acot_t : eve::elementwise_callable<acot_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acot_t, acot_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acot
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
//!      template<flx::concepts::hyperdual_like T> constexprT acot(T z) noexcept;
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
//!  @godbolt{doc/acot.cpp}
//======================================================================================================================
  inline constexpr auto acot = eve::functor<acot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acot_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::acot(e0(z));
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
        auto x2p1 = eve::inc(eve::sqr(x));
        auto rx2p1 = eve::rec(x2p1);
        ders[1] = rx2p1;
        if constexpr(ord == 1)
        {
          ders[1] = -ders[1];
          return;
        }
        else
        {
          for(unsigned short i=2; i <= ord ; ++i)
          {
            ders[i] = ders[i-1]*rx2p1;
          }
          ders[1] *= b_t(-1);
          ders[2] *= 2*x;
          if constexpr(ord == 2)   return;
          ders[3] *=2-6*x*x;
          if constexpr(ord == 3)   return;
          ders[4] *= 24*x*(x*x-1);
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
