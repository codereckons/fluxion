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
#include <fluxion/module/core/max.hpp>

namespace flx
{
  template<typename Options>
  struct negmaxabs_t : eve::callable<negmaxabs_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<Z0, Zs...> operator()(Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(z0, zs...);
    }

    flx_CALLABLE_OBJECT(negmaxabs_t, negmaxabs_);
  };

//======================================================================================================================
//! @negmaxabstogroup real
//! @{
//!   @var negmaxabs
//!   @brief Computes thethe negated maximum value of the arguments.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexpr auto negmaxabs(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the negated maximum value of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/negmaxabs.cpp}
//======================================================================================================================
  inline constexpr auto negmaxabs = eve::functor<negmaxabs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename T0, typename T1, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto negmaxabs_(flx_DELAY(), O const& o, T0 z0, T1 z1, Ts... zs) noexcept
  {
    return -flx::max(flx::abs(z0), flx::abs(z1), flx::abs(zs)...);
  }
}
