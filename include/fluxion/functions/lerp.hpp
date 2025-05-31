//======================================================================================================================
/*
  Kyosu - Hyperdual numbers
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>

namespace flx
{
  template<typename Options>
  struct lerp_t : eve::callable<lerp_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1, concepts::hyperdual_like Z2 >
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1, Z2> operator()(Z0 const& z0, Z1 const& z1, Z2 const& z2) const noexcept
    {
      return  flx_CALL(z0, z1, z2);
    }

    flx_CALLABLE_OBJECT(lerp_t, lerp_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var lerp
//!   @brief Computes z0*z1+z2
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
//!      template<concepts::hyperdual_like T0, concepts::hyperdual_like  T1, concepts::hyperdual_like  T2 > constexprT lerp(T0 z0,  T1 t1, T2, t2) noexcept;
//!   }
//!
//!   @endcode
//!
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `t`:  arguments.
//!
//!    **Return value**
//!
//!      1. The value of the interpolation (or extrapolation)  between `x` and `y` is returned.
//!         The call is semantically equivalent to `x+t*(y-x)` but uses fma opportunities.
//!      2. `pedantic` version of fma is used internally.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lerp.cpp}
//======================================================================================================================
  inline constexpr auto lerp = eve::functor<lerp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename Z1, typename Z2, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto lerp_(flx_DELAY(), O const& o, Z0 a, Z1 b, Z2 t) noexcept
  {
    return flx::fma[o](t, b, flx::fnma[o](t, a, a));
  }
}
