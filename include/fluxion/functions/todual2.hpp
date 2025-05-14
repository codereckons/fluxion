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
  struct make_dual_t : eve::callable<make_dual_t, Options>
  {
    template<concepts::dual Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& v) const noexcept
    {
     return v;
    }

    template<flx::concepts::base T>
    FLX_FORCEINLINE constexpr dual_t<T> operator()(T r)  const noexcept
    {
      return as_hyperdual_n_t<1,T>(r, T{0});
    }

    template<flx::concepts::base Val, flx::concepts::base Der>
    FLX_FORCEINLINE constexpr as_hyperdual_n_t<1, Val, Der> operator()(Val v, Der d) const noexcept
    {
      return as_hyperdual_n_t<1, Val, Der>{v, d};
    }

    flx_CALLABLE_OBJECT(make_dual_t, make_dual_);
  };

//====================================================================================================================
//! @addtogroup functions
//! @{
//!   @var dual
//!   @brief Constructs a kyosu::dual_t instance
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
//!     constexpr auto dual(auto val, auto der = 0)  noexcept;
//!     constexpr T dual(as_dual1<T> auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`      : Dual value.
//!     * `r`, `i` : val and der parts used to construct a @ref kyosu::dual.
//!
//!   **Return value**
//!
//!     Returns a @ref kyosu::dual constructed from its arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/to_dual.cpp}
//======================================================================================================================

inline constexpr auto dual = eve::functor<make_dual_t>;
//====================================================================================================================
//! @}
//====================================================================================================================
}
