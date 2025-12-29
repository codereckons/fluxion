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
#include <array>

namespace flx
{
  template<typename Options>
  struct atand_t : eve::elementwise_callable<atand_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(atand_t, atand_);
};

//======================================================================================================================
//! @adtogroup functions
//! @{
//!   @var atand
//!   @brief Computes the arc tangent in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT atand(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc tangent of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [atan](@ref atan) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atand.cpp}
//======================================================================================================================
  inline constexpr auto atand = eve::functor<atand_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto atand_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::atan(z));
  }
}
