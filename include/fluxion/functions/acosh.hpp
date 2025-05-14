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
#include <fluxion/functions/log.hpp>
#include <fluxion/functions/sqr.hpp>
#include <fluxion/functions/sqrt.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acosh_t : eve::elementwise_callable<acosh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acosh_t, acosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acosh
//!   @brief Computes the arc cosine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acosh(T z) noexcept;
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
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acosh.cpp}
//======================================================================================================================
  inline constexpr auto acosh = eve::functor<acosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto acosh_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::acosh(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return flx::log(z+flx::sqrt(z-1)*sqrt(z+1));
    }
  }
}
