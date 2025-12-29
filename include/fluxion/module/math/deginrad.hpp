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
  struct deginrad_t : eve::elementwise_callable<deginrad_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(deginrad_t, deginrad_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var deginrad
//!   @brief Computes the degree input converted in radian.
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
//!      template<flx::concepts::hyperdual_like T> T deginrad(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    the degree input converted in radian.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/deginrad.cpp}
//======================================================================================================================
  inline constexpr auto deginrad = eve::functor<deginrad_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto deginrad_(flx_DELAY(), O const&, Z a) noexcept
  {
    using T = eve::underlying_type_t<Z>;
    auto ridh = ieee_constant<0x1.1de0000p-6f, 0x1.1df46a0000000p-6>(eve::as<T>{});
    auto ridl = ieee_constant<0x1.46a2520p-18f, 0x1.294e9c8ae0ec6p-33>(eve::as<T>{});
    return fma(a, ridl, a * ridh);
  }
}
