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
#include <fluxion/functions/rec.hpp>
#include <fluxion/functions/sqrt.hpp>
//#include <eve/module/math.hpp>

namespace flx
{
  template<typename Options>
  struct tan_t : eve::elementwise_callable<tan_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(tan_t, tan_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tan
//!   @brief Computes the tangent of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T tan(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse tangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tan.cpp}
//======================================================================================================================
  inline constexpr auto tan = eve::functor<tan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto tan_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
      return eve::tan(z);
    else
      return flx::sin(z)/flx::cos(z);
  }
}
