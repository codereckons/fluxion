//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/types/dual_types.hpp>
#include <fluxion/types/traits.hpp>

namespace flx
{
  template<typename Options>
  struct make_dual3_t : eve::callable<make_dual3_t, Options>
  {
    template<concepts::hyperdual Z>
    requires(flx::order_v<Z> >= 3)
    FLX_FORCEINLINE constexpr Z operator()(Z const& v) const noexcept
    {
      return as_hyperdual_n_t<3,Z>(e0(v), e1(v), e1(v), e12(v)
                                 , e3(v), e13(v), e23(v), e123(v));
    }

    template<flx::concepts::base Val, flx::concepts::base Der, flx::concepts::base Acc, flx::concepts::base Jrk>
    FLX_FORCEINLINE constexpr as_hyperdual_n_t<3, Val, Der, Acc, Jrk> operator()(Val v, Der d, Acc a, Jrk j) const noexcept
    {
      return as_hyperdual_n_t<3, Val, Der, Acc>{ v, d, d, a
                                               , d, a, a, j};
    }

    flx_CALLABLE_OBJECT(make_dual3_t, make_dual3_);
  };

//====================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dual3
//!   @brief Constructs a kyosu::dual3_t instance
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!     constexpr auto dual3(auto val, auto der, auto acc, auto jrk)  noexcept;
//!     constexpr T dual3(as_dual3<T> auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: dual3 value.
//!     * `val`, `der`, `acc`, 'jrk': value, derivative, acceleration and jerk, parts used to construct a dual3.
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::dual3 constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_dual3.cpp}
//======================================================================================================================

inline constexpr auto dual3 = eve::functor<make_dual3_t>;
//====================================================================================================================
//! @}
//====================================================================================================================
}
