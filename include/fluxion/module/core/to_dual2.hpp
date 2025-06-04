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
  struct make_dual2_t : eve::callable<make_dual2_t, Options>
  {
    template<concepts::hyperdual Z>
    requires(flx::order_v<Z> >= 2)
    FLX_FORCEINLINE constexpr Z operator()(Z const& v) const noexcept
    {
      return as_hyperdual_n_t<2,Z>(e0(v), e1(v), e2(v), e12(v));
    }

//     template<flx::concepts::base Ts>
//     FLX_FORCEINLINE constexpr dual2_t<T> operator()(Ts r)  const noexcept
//     {
//       return as_hyperdual_n_t<2,T>(r, T{0}, T{0, T{0}});
//     }

    template<flx::concepts::base Val, flx::concepts::base Der, flx::concepts::base Acc>
    FLX_FORCEINLINE constexpr as_hyperdual_n_t<2, Val, Der> operator()(Val v, Der d, Acc a) const noexcept
    {
      return as_hyperdual_n_t<2, Val, Der, Acc>{v, d, d, a};
    }

    flx_CALLABLE_OBJECT(make_dual2_t, make_dual2_);
  };

//====================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dual2
//!   @brief Constructs a kyosu::dual2_t instance
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
//!     constexpr auto dual2(auto val, auto der, auto acc)  noexcept;
//!     constexpr T dual2(as_dual21<T> auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: dual2 value.
//!     * `val`, `der`, `acc`: value, derivative and acceleration, parts used to construct a dual2.
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::dual constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_dual.cpp}
//======================================================================================================================

inline constexpr auto dual2 = eve::functor<make_dual2_t>;
//====================================================================================================================
//! @}
//====================================================================================================================
}
