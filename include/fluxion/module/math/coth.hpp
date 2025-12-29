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
#include <fluxion/module/math/exp.hpp>

namespace flx
{
  template<typename Options>
  struct coth_t : eve::elementwise_callable<coth_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(coth_t, coth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var coth
//!   @brief Computes the hyperbolic cocotgent of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT coth(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cocotgent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/coth.cpp}
//======================================================================================================================
  inline constexpr auto coth = eve::functor<coth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto coth_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::coth(z);
    }
    else
    {
      return flx::inc(flx::exp(-2*z))/flx::oneminus(flx::exp(-2*z));
    }
  }
}
