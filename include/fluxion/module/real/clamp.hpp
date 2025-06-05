//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/module/real/abs.hpp>

namespace flx
{
  template<typename Options>
  struct clamp_t : eve::callable<clamp_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 , concepts::hyperdual_like Z2>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1, Z2> operator()(Z0 c0, Z1 c1, Z2 c2) const noexcept
    {
      return flx_CALL(c0, c1, c2);
    }

    flx_CALLABLE_OBJECT(clamp_t, clamp_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var clamp
//!   @brief clamp the first parameter between the two others.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!     // regular call
//!     constexpr auto clamp(auto z0,  auto z1)           noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, 'z2': Values to process.
//!
//!   **Return value**
//!
//!        clamp the first parameter between the two others.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/clamp.cpp}
//======================================================================================================================
  inline constexpr auto clamp = eve::functor<clamp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, typename Z2, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto clamp_(flx_DELAY(), O const& , Z0 a, Z1 l, Z2 h) noexcept
  {
    {
      auto val =  eve::clamp(flx::e0(a), flx::e0(l), flx::e0(h));
      if constexpr(concepts::base<Z0> &&  concepts::base<Z1>)
        return val;
      else
      {
        flx::as_hyperdual_like_t<Z0, Z1, Z2> r = flx::min(flx::max(a, l), h);
        e0(r) = val;
        return r;
      }
    }
  }
}
