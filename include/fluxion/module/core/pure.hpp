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
  struct pure_t : eve::elementwise_callable<pure_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(pure_t, pure_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pure
//!   @brief put to zero the e0 part of an hyperdual.
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
//!      template<flx::concepts::hyperdual T> constexpr T pure(T const& z)  noexcept;
//!      template<flx::real T>                constexpr T pure(T const& z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Original value.
//!
//!   **Return value**
//!
//!     Returns the pure (also called imaginary) part of its argument. For real inputs, the call returns 0. It is an alias of `imag`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/imag.cpp}
//======================================================================================================================

  inline constexpr auto pure = eve::functor<pure_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto pure_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>) return Z{0};
    else
    {
      e0(z) = 0;
      return z;
    }
  }
}
