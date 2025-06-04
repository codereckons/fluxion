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
#include <fluxion/functions/exp.hpp>
#include <fluxion/functions/inc.hpp>
#include <fluxion/functions/oneminus.hpp>

namespace flx
{
  template<typename Options>
  struct tanh_t : eve::elementwise_callable<tanh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(tanh_t, tanh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tanh
//!   @brief Computes the hyperbolic cotangent of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT tanh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cotangent of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tanh.cpp}
//======================================================================================================================
  inline constexpr auto tanh = eve::functor<tanh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto tanh_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::tanh(z);
    }
    else
    {
      return flx::oneminus(flx::exp(-2*z))/flx::inc(flx::exp(-2*z));
    }
  }
}
