//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>

namespace flx
{
  template<typename Options>
  struct sqr_abs_t : eve::elementwise_callable<sqr_abs_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sqr_abs_t, sqr_abs_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqr_abs
//!   @brief Computes the square of the modulus of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T sqr_abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the square of the modulus  of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqr_abs.cpp}
//======================================================================================================================
  inline constexpr auto sqr_abs = eve::functor<sqr_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto sqr_abs_(flx_DELAY(), O const&, Z z) noexcept
  {
    return z*z;
  }
}
