//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/module/real/abs.hpp>

namespace flx
{
  template<typename Options>
  struct sum_of_prod_t : eve::callable<sum_of_prod_t, Options>
  {
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 , concepts::hyperdual_like Z2, concepts::hyperdual_like Z3>
    FLX_FORCEINLINE constexpr auto/*flx::as_hyperdual_like_t<Z0, Z1, Z2, Z3>*/ operator()(Z0 c0, Z1 c1, Z2 c2, Z3 c3) const noexcept
    {
      return flx_CALL(c0, c1, c2, c3);
    }

    flx_CALLABLE_OBJECT(sum_of_prod_t, sum_of_prod_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var sum_of_prod
//!   @brief z0*z1+z1*z2.
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
//!     // regular call
//!     constexpr auto sum_of_prod(auto z0,  auto z1)           noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`, 'z2, 'z3': Values to process.
//!
//!   **Return value**
//!
//!        z0*z1+z1*z2.
//!
//!     Arguments can be a mix of floating or Hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sum_of_prod.cpp}
//======================================================================================================================
  inline constexpr auto sum_of_prod = eve::functor<sum_of_prod_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, typename Z2, typename Z3, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sum_of_prod_(flx_DELAY(), O const& , Z0 z0, Z1 z1, Z2 z2, Z3 z3) noexcept
  {
    {
      auto val =  eve::sum_of_prod(flx::e0(z0), flx::e0(z1), flx::e0(z2), flx::e0(z3));
      if constexpr(concepts::base<Z0> &&  concepts::base<Z1> &&  concepts::base<Z2> &&  concepts::base<Z3>)
        return val;
      else
      {
        auto r = z0*z1+z2*z3;
        e0(r) = val;
        return r;
      }
    }
  }
}
