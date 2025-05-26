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
  struct asecpi_t : eve::elementwise_callable<asecpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asecpi_t, asecpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asecpi
//!   @brief Computes the arc secant in pi multiples of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asecpi(T z) noexcept;
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
//!     Those of [asec](@ref asec) multiplied by the inverse of pi
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asecpi.cpp}
//======================================================================================================================
  inline constexpr auto asecpi = eve::functor<asecpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asecpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::asec(z)*eve::inv_pi(eve::as(e0(z)));
  }
}
