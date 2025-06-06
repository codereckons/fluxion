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
  struct acosd_t : eve::elementwise_callable<acosd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acosd_t, acosd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acosd
//!   @brief Computes the arc cosine in degree of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acosd(T z) noexcept;
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
//!   **Derivative values of order 1 to 4**
//!
//!     Those of [acos](@ref acos) converted in degrees
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acosd.cpp}
//======================================================================================================================
  inline constexpr auto acosd = eve::functor<acosd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acosd_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::radindeg(flx::acos(z));
  }
}
