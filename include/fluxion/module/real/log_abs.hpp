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
#include <eve/module/math.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct log_abs_t : eve::elementwise_callable<log_abs_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(log_abs_t, log_abs_);
};

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var log_abs
//!   @brief Computes the log_abs of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT log_abs(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the log_abs of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log_abs.cpp}
//======================================================================================================================
  inline constexpr auto log_abs = eve::functor<log_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
#include <span>

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto log_abs_(flx_DELAY(), O const&, Z z) noexcept
  {
    e0(z) = eve::abs(e0(z));
    return flx::log(z);
  }
}
