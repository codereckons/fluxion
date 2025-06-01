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
  struct manhattan_t : eve::callable<manhattan_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(manhattan_t, manhattan_);
  };

//======================================================================================================================
//! @manhattantogroup functions
//! @{
//!   @var manhattan
//!   @brief Computes the l1 norm of the arguments.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT manhattan(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the l1-norm of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/manhattan.cpp}
//======================================================================================================================
  inline constexpr auto manhattan = eve::functor<manhattan_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename T0, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto manhattan_(flx_DELAY(), O const& o, T0 z0, Ts... zs) noexcept
  {
    return (flx::abs(z0)+ (flx::abs(zs)+...));
  }
}
