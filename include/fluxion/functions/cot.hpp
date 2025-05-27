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
#include <fluxion/functions/tan.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct cot_t : eve::elementwise_callable<cot_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cot_t, cot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cot
//!   @brief Computes the cotangentt of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT cot(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cotangent of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$-\csc^2(x)\f$
//!     2. \f$2 \cot(x) \csc^2(x)\f$
//!     3. \f$-2 (\csc^4(x) + 2 \cot^2(x) \csc^2(x))\f$
//!     4. \f$8 \cot(x) \csc^2(x) (\cot^2(x) + 2 \csc^2(x))\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cot.cpp}
//======================================================================================================================
  inline constexpr auto cot = eve::functor<cot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cot_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::rec(flx::tan(z));
  }
}
