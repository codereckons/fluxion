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
  struct atan2_t : eve::strict_elementwise_callable<atan2_t, Options, eve::pedantic_option, eve::numeric_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr auto operator()(Z0 c0, Z1 c1) const noexcept -> decltype(flx::abs(c0-c1))
    {
      return flx_CALL(c0, c1);
    }

    flx_CALLABLE_OBJECT(atan2_t, atan2_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var atan2
//!   @brief Computes the atan2ance between the two parameters.
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
//!     constexpr auto atan2(auto z0,  auto z1)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto atan2[pedantic](auto z0,  auto z1) noexcept; //2
//!     constexpr auto atan2[numeric](auto z0,  auto z1) noexcept;  //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      1. Returns the atan2ance between the two arguments computed as the absolute value of the arguments difference.
//!         The atan2ance betwween an infinite an a nan value is nan
//!      2. if the pedantic option is used the atan2ance betwween an infinite value an anything (even a nan) is infinite.
//!      3. the numeric option implies pedantic return zero if all corresponding parts satisfy `eve::is_equal[numeric]`.
//!
//!     Arguments can be a mix of floating or hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/atan2.cpp}
//======================================================================================================================
  inline constexpr auto atan2 = eve::functor<atan2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto atan2_(flx_DELAY(), O const& o, Z0 x, Z1 y) noexcept
  {
    auto z = flx::atan(y/x);
    e0(z) = eve::atan2[o](e0(x), e0(y));
    return z;
  }
}
