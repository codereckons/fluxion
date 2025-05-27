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
#include <fluxion/functions/asinh.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acsch_t : eve::elementwise_callable<acsch_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acsch_t, acsch_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acsch
//!   @brief Computes the arg hyperbolic cosecant of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acsch(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arg hyperbolic cosecant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$\frac{-1}{ x^2\sqrt{1+1/x^2}}\f$
//!     2. \f$\frac{2x2+1}{x^3(x^2+1)\sqrt{1+1/x^2}}\f$
//!     3. \f$\frac{-6x^4-5x^2-2}{x^3(x^2+1)^2\sqrt{1+1/x^2}}\f$
//!     4. \f$-\frac{3(8x^6+8x^4+7x^2+2}{x^5(x^2+1^3)\sqrt{1+1/x^2}}\f$

//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acsch.cpp}
//======================================================================================================================
  inline constexpr auto acsch = eve::functor<acsch_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto acsch_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::acsch(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return flx::asinh(flx::rec(z));
    }
  }
}
