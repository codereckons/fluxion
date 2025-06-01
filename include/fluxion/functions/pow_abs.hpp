//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/functions/atan.hpp>
#include <eve/module/math.hpp>
namespace flx
{
  template<typename Options>
  struct pow_abs_t : eve::callable<pow_abs_t, Options, eve::raw_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z0, Z1> operator()(Z0 c0, Z1 c1) const noexcept
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(pow_abs_t, pow_abs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow_abs
//!   @brief Computes the  the pow_abs operation \f$x^y\f$.
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
//!     // regular call
//!     constexpr auto pow_abs(auto z0,  auto z1)  noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      Returns the  \f$z_0^z_1\f$.
//!
//!     Arguments can be a mix of floating and hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow_abs.cpp}
//======================================================================================================================
  inline constexpr auto pow_abs = eve::functor<pow_abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto pow_abs_(flx_DELAY(), O const& o, Z0 x, Z1 y) noexcept
  {
    return flx::pow(flx::abs(x), y); 
  }
}
