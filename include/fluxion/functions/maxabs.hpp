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
#include <fluxion/functions/max.hpp>

namespace flx
{
  template<typename Options>
  struct maxabs_t : eve::callable<maxabs_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(maxabs_t, maxabs_);
  };

//======================================================================================================================
//! @maxabstogroup functions
//! @{
//!   @var maxabs
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT maxabs(T0 z0,  Ts... zs) noexcept;
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
//!  @godbolt{doc/maxabs.cpp}
//======================================================================================================================
  inline constexpr auto maxabs = eve::functor<maxabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto maxabs_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    return flx::max(flx::abs(z0), flx::abs(z1), flx::abs(zs)...);
  }
}
