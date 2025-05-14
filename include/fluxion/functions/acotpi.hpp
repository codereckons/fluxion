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
#include <fluxion/functions/acot.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acotpi_t : eve::elementwise_callable<acotpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acotpi_t, acotpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acotpi
//!   @brief Computes the arc cotangent in pi multiples of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acotpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cotangent in pi multiples of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acotpi.cpp}
//======================================================================================================================
  inline constexpr auto acotpi = eve::functor<acotpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto acotpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::acot(z)*eve::inv_pi(eve::as(e0(z)));
  }
}
