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
#include <fluxion/module/math/log.hpp>
#include <fluxion/module/math/sqr.hpp>
#include <fluxion/module/math/sqrt.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct asech_t : eve::elementwise_callable<asech_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asech_t, asech_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asech
//!   @brief Computes the arg hyperbolic secant of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asech(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arg hyperbolic secant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!     1. \f$\frac{-1}{\sqrt{1/x-1}\sqrt{1/x+1}x^2}\f$
//!     2. \f$\frac{2 x^2 + 1}{\sqrt{1/x-1}\sqrt{1/x+1}x^3(x^2-1)^}\f$
//!     3. \f$\frac{-6x^4+5x^2-2)}{\sqrt{1/x-1}\sqrt{1/x+1}x^4(x^2-1)^2}\f$
//!     4. \f$\frac{3(8x^6-8x^4+7x^2-2)}{\sqrt{1/x-1}\sqrt{1/x+1}x^5(x^2-1)^3}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asech.cpp}
//======================================================================================================================
  inline constexpr auto asech = eve::functor<asech_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asech_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::asech(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return flx::log(rec(z)+flx::sqrt(flx::rec(z)-1)*sqrt(flx::rec(z)+1));
    }
  }
}
