//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/functions/parts.hpp>
#include <fluxion/functions/sqr.hpp>
#include <fluxion/functions/pure.hpp>

namespace flx
{
  template<typename Options>
  struct rec_t : eve::elementwise_callable<rec_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(rec_t, rec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var rec
//!   @brief Computes the inverse of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T rec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rec.cpp}
//======================================================================================================================
  inline constexpr auto rec = eve::functor<rec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto rec_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto re0 = eve::rec(e0(z));
    if constexpr(concepts::base<Z> )
    {
      return re0;
    }
    else if constexpr(order_v<Z> == 1)
    {
      return Z{re0, -sqr(re0)*e1(z)};
    }
    else
    {
      auto pz = -flx::pure(z)*re0;
      auto p1 = pz;
      Z p(eve::one(eve::as<as_base_type_t<Z>>()));
      for(unsigned short i=0; i < order_v<Z>; ++i)
      {
        p += p1;
        p1 *= pz;
      }
      return p*re0;
    }
  }
}
