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
  struct asecd_t : eve::elementwise_callable<asecd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asecd_t, asecd_);
};

//======================================================================================================================
//! @adtogroup functions
//! @{
//!   @var asecd
//!   @brief Computes the arc secant in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asecd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc secant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [asecd](@ref asecd) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asecd.cpp}
//======================================================================================================================
  inline constexpr auto asecd = eve::functor<asecd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asecd_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::asec(z));
  }
}
