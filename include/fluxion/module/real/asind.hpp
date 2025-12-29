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
  struct asind_t : eve::elementwise_callable<asind_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asind_t, asind_);
};

//======================================================================================================================
//! @adtogroup functions
//! @{
//!   @var asind
//!   @brief Computes the arc sine in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asind(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc sine of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [asin](@ref asin) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asind.cpp}
//======================================================================================================================
  inline constexpr auto asind = eve::functor<asind_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asind_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::asin(z));
  }
}
