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
#include <eve/module/special.hpp>



namespace flx
{
  template<typename Options>
  struct log_gamma_t : eve::elementwise_callable<log_gamma_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log_gamma
//!   @brief Computes the logarithm of the gamma function.
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
//!      constexpr auto log_gamma(floating_value auto x)   noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: argument.
//!
//!    **Return value**
//!
//!     The value of the logarithm of the gamma function
//!
//!  @warning only the first derivative is currently implemented
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/log_gamma.cpp}
//======================================================================================================================
  inline constexpr auto log_gamma = eve::functor<log_gamma_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto log_gamma_(flx_DELAY(), O const&, Z z) noexcept
  requires(concepts::base<Z> || order_v<Z> == 1)
  {
    auto val= eve::log_gamma(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      ders[1] = eve::digamma(e0(z));
      return _::evaluate(ders, z);
    }
  }
}
