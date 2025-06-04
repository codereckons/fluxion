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
  struct is_denormal_t : eve::elementwise_callable<is_denormal_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(is_denormal_t, is_denormal_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_denormal
//!   @brief test if the parameter is denormal.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto is_denormal(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is the val component of z is denormal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_denormal.cpp}
//======================================================================================================================
  inline constexpr auto is_denormal = eve::functor<is_denormal_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_denormal_(flx_DELAY(), O const&, Z z) noexcept
  {
    return eve::is_denormal(e0(z));
  }
}
