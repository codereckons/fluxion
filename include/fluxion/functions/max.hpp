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
#include <fluxion/functions/is_less.hpp>


namespace flx
{
  template<typename Options>
  struct max_t : eve::callable<max_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(max_t, max_);
  };

//======================================================================================================================
//! @maxtogroup functions
//! @{
//!   @var max
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT max(T0 z0,  Ts... zs) noexcept;
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
//!  @godbolt{doc/max.cpp}
//======================================================================================================================
  inline constexpr auto max = eve::functor<max_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto max_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    using r_t = flx::as_hyperdual_like_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0) // 2 parameters
    {
      r_t z(flx::if_else(flx::is_less[o](z0, z1), z1, z0));
      return z;
    }
    else // N > 2 parameters
    {
      auto m = flx::max[o];
      r_t that(m(z0, z1));
      ((that = m(that, zs)), ...);
      return that;
    }
  }
}
