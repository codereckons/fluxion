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
#include <fluxion/functions/acos.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acospi_t : eve::elementwise_callable<acospi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acospi_t, acospi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acospi
//!   @brief Computes the arc cosine in pi multiples of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acospi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cosine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acospi.cpp}
//======================================================================================================================
  inline constexpr auto acospi = eve::functor<acospi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acospi_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::acos(z)*eve::inv_pi(eve::as(e0(z)));
  }
}
