//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/functions/atan.hpp>
#include <eve/module/math.hpp>
namespace flx
{
  template<typename Options>
  struct am_t : eve::strict_elementwise_callable<am_t, Options, threshold_option, modular_option, eccentric_option>
  {
   template<concepts::hyperdual_like Z0, concepts::base U >
    FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z0,U> operator()(Z0 z, U m) const noexcept
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
    auto tol = [&](){
      if constexpr (O::contains(threshold)) return o[threshold].value(x);
      else                                  return eps(as(element_type_t<M>()));
    }();
    x =  abs(e0(x));
    if constexpr(O::contains(modular)) x = eve::sin(x);
    else if constexpr(O::contains(eccentric)) x = eve::sqrt(x);
    auto phi = am[eve::threshold = tol](u, x);
    auto m =  x*x;
    if constexpr(concepts::base<Z>)
    {
      return phi;
    }
    else
    {
      constexpr auto ord = flx::order_v<Z>;
      auto [sn, cn] = eve::sincos(phi);
      auto dn = eve::sqrt(eve::oneminus(m*eve::sqr(sn)));
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,ord+1> ders;
      ders[0] = am;
      ders[1] = dn;
      if constexpr(ord == 1) return;
      else
      {
        ders[2] = -m*sn*cn;
        if constexpr(ord == 2) return;
        else
        {
          ders[3] = -m*dn(cn*cn-sn*sn);
          if constexpr(ord == 3) return;
          else
          {
            ders[4] = m*cn*sn*(m*(cn*cn-sn*sn)+4*dn*dn);
          }
        }
      };
      comp_ders(e0(u));
      return _::evaluate(ders, z);
    }
  }
}
