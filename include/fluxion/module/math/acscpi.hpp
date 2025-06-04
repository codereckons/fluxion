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
#include <fluxion/module/math/acsc.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acscpi_t : eve::elementwise_callable<acscpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acscpi_t, acscpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acscpi
//!   @brief Computes the arc cosecant in pi multiples of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acscpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cosecant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [acos](@ref acsc) multiplied by the inverse of pi
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acscpi.cpp}
//======================================================================================================================
  inline constexpr auto acscpi = eve::functor<acscpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acscpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::acsc(z)*eve::inv_pi(eve::as(e0(z)));
  }
}
