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
  struct dec_t : eve::elementwise_callable<dec_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(dec_t, dec_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dec
//!   @brief Computes the argument minus one.
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
//!      template<flx::concepts::hyperdual_like T> constexprT dec(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the argument minus one.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dec.cpp}
//======================================================================================================================
  inline constexpr auto dec = eve::functor<dec_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto dec_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::dec(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return z-one(eve::as(e0(z)));
    }
  }
}
