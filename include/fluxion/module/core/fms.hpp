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
  struct fms_t : eve::callable<fms_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1, concepts::hyperdual_like Z2 >
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Z1, Z2> operator()(Z0 const& z0, Z1 const& z1, Z2 const& z2) const noexcept
    {
      return  flx_CALL(z0, z1, z2);
    }

    flx_CALLABLE_OBJECT(fms_t, fms_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var fms
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT fms(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, `z2`: Values to process.
//!
//!   **Return value**
//!
//!     Returns  z0+z1*z2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/fms.cpp}
//======================================================================================================================
  inline constexpr auto fms = eve::functor<fms_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z0, typename Z1, typename Z2, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto fms_(flx_DELAY(), O const&, Z0 z0, Z1 z1, Z2 z2) noexcept
  {
    auto r = z0*z1-z2;
    flx::e0(r) = eve::fms(e0(z0), e0(z1), e0(z2));
    return r;
  }
}
