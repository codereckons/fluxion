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
  struct add_t : eve::callable<add_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    requires(concepts::hyperdual<Z0> || (concepts::hyperdual<Zs> || ...))
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(add_t, add_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var add
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT add(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the sum of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/add.cpp}
//======================================================================================================================
  inline constexpr auto add = eve::functor<add_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename ... Zs, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto add_(flx_DELAY(), O const&, Z0 z0, Zs... zs) noexcept
  {
    return z0+(zs+...);
  }
}
