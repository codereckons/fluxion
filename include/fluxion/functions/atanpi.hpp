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
  struct atanpi_t : eve::elementwise_callable<atanpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(atanpi_t, atanpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atanpi
//!   @brief Computes the arc tangent in pi multiples of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT atanpi(T z) noexcept;
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
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atanpi.cpp}
//======================================================================================================================
  inline constexpr auto atanpi = eve::functor<atanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto atanpi_(flx_DELAY(), O const&, Z z) noexcept
  {
//    std::cout << eve::inv_pi(eve::as(e0(z))) << std::endl;
    return flx::atan(z)*eve::inv_pi(eve::as(e0(z)));
  }
}
