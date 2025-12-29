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
  struct radindeg_t : eve::elementwise_callable<radindeg_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(radindeg_t, radindeg_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var radindeg
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
//!      template<flx::concepts::hyperdual_like T> T radindeg(T z) noexcept;
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
//!  @godbolt{doc/radindeg.cpp}
//======================================================================================================================
  inline constexpr auto radindeg = eve::functor<radindeg_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto radindeg_(flx_DELAY(), O const&, Z a) noexcept
  {
    using T = eve::underlying_type_t<Z>;
    auto radradindeg  = ieee_constant<0x1.ca5dc20p+5f, 0x1.ca5dc1a63c1f8p+5>(eve::as<T>{});
    auto radradindegr = ieee_constant<0x1.670f800p-21f, 0x1.1e7ab456405f8p-49>(eve::as<T>{});
    return fma(a, radradindegr, a * radradindeg);
  }
}
