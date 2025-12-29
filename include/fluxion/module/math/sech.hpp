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
#include <fluxion/module/math/sinh.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct sech_t : eve::elementwise_callable<sech_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sech_t, sech_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sech
//!   @brief Computes the hyperbolic secant of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT sech(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic secant of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sech.cpp}
//======================================================================================================================
  inline constexpr auto sech = eve::functor<sech_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sech_(flx_DELAY(), O const&, Z z) noexcept
  {
    return flx::rec(flx::cosh(z));
  }
}
