//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <eve/module/math.hpp>
#include <fluxion/details/mula.hpp>

namespace flx
{
  template<typename Options>
  struct expm1_t : eve::elementwise_callable<expm1_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(expm1_t, expm1_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expm1
//!   @brief Computes the  exponential minus one of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpm1r T expm1(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the base 2 exponential minus one of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/expm1.cpp}
//======================================================================================================================
  inline constexpr auto expm1 = eve::functor<expm1_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto expm1_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val =eve::expm1(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      auto r = exp(z);
      e0(r) = val;
      return r;
    }
  }
}
