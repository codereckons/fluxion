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
#include <fluxion/module/real/abs.hpp>
#include <fluxion/module/real/max.hpp>

namespace flx
{
  template<typename Options>
  struct absmax_t : eve::callable<absmax_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(absmax_t, absmax_);
  };

//======================================================================================================================
//! @absmaxtogroup real
//! @{
//!   @var absmax
//!   @brief Computes the absolute value of the maximal element.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT absmax(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the absolute value of the maximal element.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/absmax.cpp}
//======================================================================================================================
  inline constexpr auto absmax = eve::functor<absmax_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto absmax_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    return flx::abs(flx::max(z0, z1, zs...));
  }
}
