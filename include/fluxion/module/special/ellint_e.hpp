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
#include <fluxion/functions/sqrt.hpp>
#include <fluxion/functions/oneminus.hpp>
#include <eve/module/elliptic.hpp>

namespace flx
{
  template<typename Options>
  struct elliptic_e_t : eve::elementwise_callable<elliptic_e_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(elliptic_e_t, elliptic_e_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var elliptic_e
//!   @brief Computes the argument tangent hyperbolic of the argument.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//======================================================================================================================
  inline constexpr auto elliptic_e = eve::functor<elliptic_e_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto elliptic_e_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto [_, val]= eve::ellint_fe(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      b_t m(1);
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto g = [](auto x, auto m){return flx::sqrt(oneminus(m*flx::sqr(flx::sin(x)))); };
      dersfromderfunc(ders, g, z, m);
      return _::evaluate(ders, z);
    }
  }
}
