//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>
#include <eve/module/core.hpp>

namespace flx
{
  template<typename Options>
  struct radinpi_t : eve::elementwise_callable<radinpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(radinpi_t, radinpi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var radinpi
//!   @brief Computes the radian input converted in \f$\pi\f$ multiples.
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
//!      //regular calls
//!      template<flx::concepts::hyperdual_like T> T radinpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    the radian input converted in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/radinpi.cpp}
//======================================================================================================================
  inline constexpr auto radinpi = eve::functor<radinpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto radinpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    return eve::inv_pi(eve::as(e0(z))) * z;
  }
}
