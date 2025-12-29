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
#include <fluxion/module/math/acos.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acotd_t : eve::elementwise_callable<acotd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acotd_t, acotd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acotd
//!   @brief Computes the arc cotangent in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acotd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cotangent of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [acot](@ref acot) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acotd.cpp}
//======================================================================================================================
  inline constexpr auto acotd = eve::functor<acotd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acotd_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::acot(z));
  }
}
