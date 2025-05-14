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

//     template<flx::concepts::base T>
//     FLX_FORCEINLINE constexpr dual_t<T> operator()(T r)  const noexcept
//     {
//       return as_hyperdual_n_t<1,T>(r, T{0});
//     }

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
//!   @brief Constructs a flx::dual_t instance
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
//!     constexpr auto dual(auto val, auto der)  noexcept;
//!     constexpr T dual(as_dual1<T> auto z)  noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Dual value.
//!     * `val`, `der`: value and derivative parts used to construct a dual.
//!
//!   **Return value**
//!
//!     Returns a @ref flx::dual constructed from its arguments.
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
