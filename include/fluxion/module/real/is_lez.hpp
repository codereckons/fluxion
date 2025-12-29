//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>

namespace flx
{
  template<typename Options>
  struct is_lez_t : eve::strict_elementwise_callable<is_lez_t, Options>
  {
   template<concepts::hyperdual_like Z0>
   FLX_FORCEINLINE constexpr auto operator()(Z0 c0) const noexcept// -> decltype(flx::e0(c0) == flx::e0(c1))
    {
      return flx_CALL(c0);
    }

    flx_CALLABLE_OBJECT(is_lez_t, is_lez_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var is_lez
//!   @brief Computes z <= 0.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!     // regular call
//!     constexpr auto is_lez(auto z)           noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!      Returns z <= 0
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_lez.cpp}
//======================================================================================================================
  inline constexpr auto is_lez = eve::functor<is_lez_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_lez_(flx_DELAY(), O const &, Z c) noexcept
  {
    {
      return eve::is_lez(flx::e0(c));
    }
  }
}
