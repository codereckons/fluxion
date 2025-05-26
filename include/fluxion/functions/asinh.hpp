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
  struct asinh_t : eve::elementwise_callable<asinh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(asinh_t, asinh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var asinh
//!   @brief Computes the arc sine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT asinh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc sine of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!     1. \f$\frac{1}{ \sqrt{x^2+1}}\f$
//!     2. \f$\frac{x}{(1+x^2)^{3/2}}\f$
//!     3. \f$\frac{2x^2-1}{(1+x^2)^{5/2}}\f$
//!     4. \f$-\frac{3x(3-2x^2)}{(1+x^2)^{7/2}}\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/asinh.cpp}
//======================================================================================================================
  inline constexpr auto asinh = eve::functor<asinh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto asinh_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::asinh(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return flx::log(z+flx::sqrt(z*z-1));
    }
  }
}
