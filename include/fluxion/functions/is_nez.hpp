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
  struct is_nez_t : eve::elementwise_callable<is_nez_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr eve::as_logical_t<Z> operator()(Z const& z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(is_nez_t, is_nez_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_nez
//!   @brief test if the parameter is nez.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto is_nez(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns elementwise true is the val component of z is nez.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_nez.cpp}
//======================================================================================================================
  inline constexpr auto is_nez = eve::functor<is_nez_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_nez_(flx_DELAY(), O const&, Z z) noexcept
  {
    return eve::is_nez(e0(z));
  }
}
