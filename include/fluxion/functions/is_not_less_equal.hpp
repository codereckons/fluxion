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
  struct is_not_less_equal_t : eve::strict_elementwise_callable<is_not_less_equal_t, Options, eve::pedantic_option, eve::numeric_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
   FLX_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept// -> decltype(flx::e0(c0) == flx::e0(c1))
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(is_not_less_equal_t, is_not_less_equal_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var is_not_less_equal
//!   @brief Computes the is_not_less_equal between the two parameters.
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
//!     constexpr auto is_not_less_equal(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto is_not_less_equal[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto is_not_less_equal[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the is_not_less_equalance between the two arguments computed as the absolute value of the arguments difference.
//!         The is_not_less_equalance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used  is_not_less_equal betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::is_not_less_equal[numeric]`.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/is_not_less_equal.cpp}
//======================================================================================================================
  inline constexpr auto is_not_less_equal = eve::functor<is_not_less_equal_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto is_not_less_equal_(flx_DELAY(), O const& o, Z0 c0, Z1 c1) noexcept
  {
    {
      return eve::is_not_less_equal[o](flx::e0(c0), flx::e0(c1));
    }
  }
}
