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
  struct ldiv_t : eve::callable<ldiv_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(ldiv_t, ldiv_);
  };

//======================================================================================================================
//! @ldivtogroup functions
//! @{
//!   @var ldiv
//!   @brief Computes the  product of all elements but the first divided by the first.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT ldiv(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the   product of all elements but the first divided by the first.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/ldiv.cpp}
//======================================================================================================================
  inline constexpr auto ldiv = eve::functor<ldiv_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename ... Zs, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto ldiv_(flx_DELAY(), O const&, Z0 z0, Zs... zs) noexcept
  {
    return (zs*...)/z0;
  }
}
