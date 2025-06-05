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
  struct heaviside_t : eve::strict_elementwise_callable<heaviside_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1> operator()(Z0 c0, Z1 c1) const noexcept
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(heaviside_t, heaviside_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var heaviside
//!   @brief Computes the heaviside between the two parameters.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!     // regular call
//!     constexpr auto heaviside(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto heaviside[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto heaviside[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the heavisideance between the two arguments computed as the absolute value of the arguments difference.
//!         The heavisideance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used  heaviside betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::heaviside[numeric]`.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/heaviside.cpp}
//======================================================================================================================
  inline constexpr auto heaviside = eve::functor<heaviside_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto heaviside_(flx_DELAY(), O const& o, Z0 c0, Z1 c1) noexcept
  {
    {
      auto val =  eve::heaviside(flx::e0(c0), flx::e0(c1));
      if constexpr(concepts::base<Z0> &&  concepts::base<Z1>)
        return val;
      else
      {
        auto r = flx::as_hyperdual_like_t<Z0, Z1>(0);
        e0(r) = val;
        return r;
      }
    }
  }
}
