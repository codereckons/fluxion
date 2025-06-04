//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/module/real/pow_abs.hpp>
#include <fluxion/module/real/manhattan.hpp>
#include <fluxion/module/real/maxabs.hpp>

namespace flx
{
  template<typename Options>
  struct lpnorm_t : eve::callable<lpnorm_t, Options>
  {
    template<concepts::hyperdual_like P, concepts::hyperdual_like Z0, concepts::hyperdual_like ... Zs>
    FLX_FORCEINLINE constexpr flx::as_hyperdual_like_t<P, Z0, Zs...> operator()(P const & p, Z0 const& z0, Zs const& ... zs) const noexcept
    {
      return  flx_CALL(p, z0, zs...);
    }

    flx_CALLABLE_OBJECT(lpnorm_t, lpnorm_);
  };

//======================================================================================================================
//! @lpnormtogroup real
//! @{
//!   @var lpnorm
//!   @brief Computes the lp norm of the arguments.
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
//!      template<concepts::hyperdual_like T0, oncepts::hyperdual_like ... Ts > constexprT lpnorm(T0 z0,  Ts... zs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`,  `zs...`: Values to process.
//!
//!   **Return value**
//!
//!     Returns the lp-norm of the arguments.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/lpnorm.cpp}
//======================================================================================================================
  inline constexpr auto lpnorm = eve::functor<lpnorm_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename P, typename T0, typename ... Ts, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto lpnorm_(flx_DELAY(), O const& o, P p, T0 z0, Ts... zs) noexcept
  {
    if constexpr(eve::integral_scalar_value<P>)
    {
      if (p == 1) return manhattan(z0, zs...);
      else if (p == 2) return hypot(z0, zs...);
      else
      {
        using f_t =  eve::as_floating_point_t<P>;
        auto pp = f_t(p);
        return lpnorm(pp, z0, zs...);
      }
    }
    else
    {
      if (eve::all(p == 1)) return flx::manhattan(z0, zs...);
      else if (eve::all(p == 2)) return flx::hypot(z0, zs...);
      else if (eve::all(eve::is_pinf(p))) return flx::maxabs(z0, zs...);
      else return flx::pow_abs(flx::pow_abs(z0, p)+ (flx::pow_abs(zs, p)+...), flx::rec(p));
    }
  }
}
