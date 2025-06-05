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
#include <fluxion/module/real/signnz.hpp>

namespace flx
{
  template<typename Options>
  struct copysign_t : eve::callable<copysign_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1> operator()(Z0 c0, Z1 c1) const noexcept
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(copysign_t, copysign_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var copysign
//!   @brief Computes the copysign between the two parameters.
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
//!     constexpr auto copysign(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto copysign[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto copysign[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the copysignance between the two arguments computed as the absolute value of the arguments difference.
//!         The copysignance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used  copysign betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::copysign[numeric]`.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/copysign.cpp}
//======================================================================================================================
  inline constexpr auto copysign = eve::functor<copysign_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto copysign_(flx_DELAY(), O const& o, Z0 c0, Z1 c1) noexcept
  {
    {
      auto val =  eve::copysign[o](flx::e0(c0), flx::e0(c1));
      if constexpr(concepts::base<Z0> &&  concepts::base<Z1>)
        return val;
      else
      {
        flx::as_hyperdual_like_t<Z0, Z1> r(flx::abs(c0)*eve::signnz(e0(c1)));
        e0(r) = val;
        return r;
      }
    }
  }
}
