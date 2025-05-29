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
#include <fluxion/details/dersfromder.hpp>
#include <fluxion/functions/sqr.hpp>
#include <fluxion/functions/exp.hpp>
#include <eve/module/special.hpp>



namespace flx
{
  template<typename Options>
  struct erf_t : eve::elementwise_callable<erf_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(erf_t, erf_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erf
//!   @brief Computes the error function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto erf(floating_value auto x)   noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: argument.
//!
//!    **Return value**
//!
//!     The value of the error function
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/erf.cpp}
//======================================================================================================================
  inline constexpr auto erf = eve::functor<erf_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto erf_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val= eve::erf(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      constexpr auto tosqtpi = eve::two_o_sqrt_pi(eve::as<eve::underlying_type_t<b_t>>()); ;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto der = [tosqtpi](auto x){ return tosqtpi*flx::exp(-flx::sqr(x)); };
      dersfromder<0, flx::order_v<Z>>(ders, der, e0(z));
      for(int i=0; i <= flx::order_v<Z>; ++i)
      return _::evaluate(ders, z);
    }
  }
}
