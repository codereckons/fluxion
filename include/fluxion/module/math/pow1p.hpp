//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/module/math/atan.hpp>
#include <eve/module/math.hpp>
namespace flx
{
  template<typename Options>
  struct pow1p_t : eve::callable<pow1p_t, Options, eve::raw_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(pow1p_t, pow1p_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow1p
//!   @brief Computes the  the pow1p operation \f$x^y+1\f$.
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
//!     constexpr auto pow1p(auto z0,  auto z1)  noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      Returns   \f$z_0^z_1+1\f$.
//!
//!     Arguments can be a mix of floating and hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow1p.cpp}
//======================================================================================================================
  inline constexpr auto pow1p = eve::functor<pow1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto pow1p_(flx_DELAY(), O const& o, Z0 x, Z1 y) noexcept
  {
    auto val = eve::pow1p[o](e0(x), e0(y));
    if constexpr(concepts::base<Z0> && concepts::base<Z1>)
    {
      return val;
    }
    else
    {
      auto r = flx::pow[o](x+1, y);
      e0(r) = val;
      return r;
    }
  }
}
