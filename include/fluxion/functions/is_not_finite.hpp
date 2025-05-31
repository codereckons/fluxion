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

namespace flx
{
  template<typename Options>
  struct is_not_finite_t : eve::elementwise_callable<is_not_finite_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(is_not_finite_t, is_not_finite_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_finite
//!   @brief test if the parameter is not_finite.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto is_not_finite(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is the val component of z is not_finite.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_finite.cpp}
//======================================================================================================================
  inline constexpr auto is_not_finite = eve::functor<is_not_finite_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_not_finite_(flx_DELAY(), O const&, Z z) noexcept
  {
    return eve::is_not_finite(e0(z));
  }
}
