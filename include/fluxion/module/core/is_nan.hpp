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
  struct is_nan_t : eve::elementwise_callable<is_nan_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(is_nan_t, is_nan_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nan
//!   @brief test if the parameter is nan.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto is_nan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is the val component of z is nan.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nan.cpp}
//======================================================================================================================
  inline constexpr auto is_nan = eve::functor<is_nan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_nan_(flx_DELAY(), O const&, Z z) noexcept
  {
    return eve::is_nan(e0(z));
  }
}
