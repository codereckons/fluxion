//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>
#include <fluxion/types/operators.hpp>

namespace flx
{
  template<typename Options>
  struct min_t : eve::callable<min_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(min_t, min_);
  };

//======================================================================================================================
//! @mintogroup functions
//! @{
//!   @var min
//!   @brief Computes the sum of the arguments.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT min(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the sum of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/min.cpp}
//======================================================================================================================
  inline constexpr auto min = eve::functor<min_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto min_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    using r_t = flx::as_hyperdual_like_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      r_t z(flx::if_else(flx::is_less[o](z0, z1), z0, z1));
      return z;
    }
    else // N > 2 parameters
    {
      auto m = flx::min[o];
      r_t that(m(z0, z1));
      ((that = m(that, zs)), ...);
      return that;
    }
  }
}
