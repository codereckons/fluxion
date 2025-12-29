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
#include <fluxion/module/math/sqrt.hpp>

namespace flx
{
  template<typename Options>
  struct rsqrt_t : eve::elementwise_callable<rsqrt_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(rsqrt_t, rsqrt_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var rsqrt
//!   @brief Computes the inverse square root of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T rsqrt(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse square root of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/rsqrt.cpp}
//======================================================================================================================
  inline constexpr auto rsqrt = eve::functor<rsqrt_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto rsqrt_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::rsqrt(z);
    }
    else
    {
      return flx::sqrt(flx::rec(z));
    }
  }
}
