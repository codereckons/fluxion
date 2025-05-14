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
  struct inc_t : eve::elementwise_callable<inc_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(inc_t, inc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var inc
//!   @brief Computes the argument plus one.
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
//!      template<flx::concepts::hyperdual_like T> constexprT inc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the argument plus one.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/inc.cpp}
//======================================================================================================================
  inline constexpr auto inc = eve::functor<inc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto inc_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::inc(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return z+1;
    }
  }
}
