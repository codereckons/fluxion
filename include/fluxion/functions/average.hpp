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
  struct average_t : eve::callable<average_t, Options, raw_option, upper_option, lower_option, strict_option>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(average_t, average_);
  };

//======================================================================================================================
//! @averagetogroup functions
//! @{
//!   @var average
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT average(T0 z0,  Ts... zs) noexcept;
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
//!  @godbolt{doc/average.cpp}
//======================================================================================================================
  inline constexpr auto average = eve::functor<average_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename ... Zs, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto average_(flx_DELAY(), O const& o, Z0 z0, Zs... zs) noexcept
  {
    auto z = flx::add(z0, zs...)/(sizeof...(zs) + 1);
    e0(z) = eve::average[o](e0(z0), e0(zs)...);
    return z;
  }
}
