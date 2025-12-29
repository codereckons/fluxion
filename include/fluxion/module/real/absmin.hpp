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
#include <fluxion/module/core/min.hpp>

namespace flx
{
  template<typename Options>
  struct absmin_t : eve::callable<absmin_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(absmin_t, absmin_);
  };

//======================================================================================================================
//! @absmintogroup real
//! @{
//!   @var absmin
//!   @brief Computes the absolute value of the minimal element.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT absmin(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the absolute value of the minimal element.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/absmin.cpp}
//======================================================================================================================
  inline constexpr auto absmin = eve::functor<absmin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto absmin_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    return flx::abs(flx::min(z0, z1, zs...));
  }
}
