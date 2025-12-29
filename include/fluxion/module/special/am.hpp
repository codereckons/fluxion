//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/module/math/atan.hpp>
#include <eve/module/elliptic.hpp>

namespace flx
{
  template<typename Options>
  struct am_t : eve::callable<am_t, Options, eve::threshold_option, eve::modular_option, eve::eccentric_option>
  {
   template<concepts::hyperdual_like Z0, concepts::base U >
   FLX_FORCEINLINE constexpr /*as_hyperdual_like_t<Z0,U>*/ auto operator()(Z0 z, U m) const noexcept
    {
      return flx_CALL(z, m);
    }

    flx_CALLABLE_OBJECT(am_t, am_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var am
//!   @brief Computes the am jacobi elliptic function and its derivatives relative to the first parameter.
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
//!     // regular call
//!     constexpr auto am(auto z0,  auto u)           noexcept; //1
//!
//!     // Semantic modifyiers
//!     constexpr auto jacobi_elliptic[modular](auto z, floating_value auto alpha)     noexcept; // 1
//!     constexpr auto jacobi_elliptic[eccentric(auto z, floating_value auto k)        noexcept; // 1
//!     constexpr auto jacobi_elliptic[threshold = tol](auto z, floating_value auto m) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      constexpr auto am[modular](auto z, floating_value auto alpha)     noexcept; // 1
//!      constexpr auto am[eccentric(auto z, floating_value auto k)        noexcept; // 1
//!      constexpr auto am[threshold = tol](auto z, floating_value auto x) noexcept; // 2
//!
//!   **Return value**
//!
//!      1. return the jacobian amplitude function. Take care that the meaning of the second parameters
//!         depends on the option used (see note below).
//!      2. a threshold can be given controlling the needed accuracy.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/am.cpp}
//======================================================================================================================
  inline constexpr auto am = eve::functor<am_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, typename M, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto am_(flx_DELAY(), O const& o, Z u, M x) noexcept
  {
    auto phi = eve::am[o](e0(u), x);
    auto m =  x*x;
    if constexpr(concepts::base<Z>)
    {
      return phi;
    }
    else
    {
      constexpr auto ord = flx::order_v<Z>;
      auto [sn, cn, dn] = eve::jacobi_elliptic[o](e0(u), x);
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,ord+1> ders;
      ders[0] = phi;
      ders[1] = dn;
      if constexpr(ord == 1) return;
      else
      {
        ders[2] = -m*sn*cn;
        if constexpr(ord == 2) return;
        else
        {
          auto cn2msn2 = eve::diff_of_prod(cn, cn, sn, sn);
          ders[3] = -m*dn*cn2msn2;
          if constexpr(ord == 3) return;
          else
          {
            ders[4] = m*cn*sn*eve::sum_of_prod(m, cn2msn2, 2*dn, 2*dn);
          }
        }
      };
      return _::evaluate(ders, u);
   }
  }
}
