//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>

namespace flx
{
  template<typename Options>
  struct is_less_t : eve::strict_elementwise_callable<is_less_t, Options, eve::pedantic_option, eve::numeric_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
   FLX_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept// -> decltype(flx::e0(c0) == flx::e0(c1))
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(is_less_t, is_less_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_less
//!   @brief Computes the is_less between the two parameters.
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
//!     constexpr auto is_less(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto is_less[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto is_less[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the is_lessance between the two arguments computed as the absolute value of the arguments difference.
//!         The is_lessance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used  is_less betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::is_less[numeric]`.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_less.cpp}
//======================================================================================================================
  inline constexpr auto is_less = eve::functor<is_less_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_less_(flx_DELAY(), O const& o, Z0 c0, Z1 c1) noexcept
  {
    {
      return eve::is_less[o](flx::e0(c0), flx::e0(c1));
    }
  }
}
