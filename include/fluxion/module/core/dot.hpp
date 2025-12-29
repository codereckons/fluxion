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
  struct dot_t : eve::callable<dot_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1> operator()(Z0 const& z0, Z1 z1) const noexcept
    {
      return  flx_CALL(z0, z1);
    }

    flx_CALLABLE_OBJECT(dot_t, dot_);
  };

//======================================================================================================================
//! @dottogroup functions
//! @{
//!   @var dot
//!   @brief Computes the scalar product of the arguments.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT dot(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `z1`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the z0*z1 of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/dot.cpp}
//======================================================================================================================
  inline constexpr auto dot = eve::functor<dot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto dot_(flx_DELAY(), O const&, Z0 z0, Z1 z1) noexcept
  {
    return z0*z1;
  }
}
