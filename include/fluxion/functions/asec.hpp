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
#include <fluxion/functions/asin.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct asec_t : eve::elementwise_callable<asec_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asec_t, asec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asec
//!   @brief Computes the arc secant of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc secant of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$\frac{1}{\sqrt{1-1/x^2}} x^2,
//!     2. \f$\frac{1-2 x^2}/{\sqrt{1-/x^2}x^3(x^2-1)},
//!     3. \f$\frac{6x^4-5x^2+2}{\sqrt{1-1/x^2}x^4(x^2-1)^2},
//!     4. \f$-\frac{3(8x^6-8x^4+7x^2-2){(\sqrt{1-1/x^2}x^5(x^2-1)^3)}
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asec.cpp}
//======================================================================================================================
  inline constexpr auto asec = eve::functor<asec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asec_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::acos(flx::rec(z));
  }
}
