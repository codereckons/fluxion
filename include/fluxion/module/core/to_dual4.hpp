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
  struct make_dual4_t : eve::callable<make_dual4_t, Options>
  {
    template<concepts::hyperdual Z>
    requires(flx::order_v<Z> >= 4)
    FLX_FORCEINLINE constexpr Z operator()(Z const& v) const noexcept
    {
      return as_hyperdual_n_t<4,Z>(e0(v), e1(v), e1(v), e12(v)
                                 , e3(v), e13(v), 23(v), e123(v)
                                 , e4(v), e14(v), e24(v), e34(v), e124(v), e134(v), e134(v), e1234(v) );
    }

    template<flx::concepts::base Val, flx::concepts::base Der, flx::concepts::base Acc, flx::concepts::base Jrk, flx::concepts::base Snp>
    FLX_FORCEINLINE constexpr as_hyperdual_n_t<4, Val, Der, Acc, Jrk> operator()(Val v, Der d, Acc a, Jrk j, Snp s) const noexcept
    {
      return as_hyperdual_n_t<4, Val, Der, Acc>{ v, d, d, a
                                               , d, a, a, j
                                               , d, a, a, a, j, j, j, s};
    }

    flx_CALLABLE_OBJECT(make_dual4_t, make_dual4_);
  };

//====================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dual4
//!   @brief Constructs a kyosu::dual4_t instance
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
//!     constexpr auto dual4(auto val, auto der, auto acc, auto jrk, auto snp)  noexcept;
//!     constexpr T dual4(as_dual4<T> auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: dual4 value.
//!     * `val`, `der`, `acc`, 'jrk', 'snp': value, derivative, acceleration jerk, and snap, parts used to construct a dual4.
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::dual4 constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_dual4.cpp}
//======================================================================================================================

inline constexpr auto dual4 = eve::functor<make_dual4_t>;
//====================================================================================================================
//! @}
//====================================================================================================================
}
