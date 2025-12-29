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
#include <fluxion/module/math/acot.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acscd_t : eve::elementwise_callable<acscd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acscd_t, acscd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acscd
//!   @brief Computes the arc cosecant in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acscd(T z) noexcept;
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
//!     Those of [acsc](@ref acsc) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acscd.cpp}
//======================================================================================================================
  inline constexpr auto acscd = eve::functor<acscd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acscd_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::acsc(z));
  }
}
