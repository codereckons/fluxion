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
#include <eve/module/math.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct log10_t : eve::elementwise_callable<log10_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(log10_t, log10_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log10
//!   @brief Computes the log10 of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT log10(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the log10 of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log10.cpp}
//======================================================================================================================
  inline constexpr auto log10 = eve::functor<log10_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
#include <span>

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto log10_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::log10(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      constexpr auto invlog_10 = eve::invlog_10(eve::as<eve::underlying_type_t<b_t>>()); ;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto der = [invlog_10](auto x){ return invlog_10*flx::rec(x); };
      dersfromder<0, flx::order_v<Z>>(ders, der, e0(z));
      return _::evaluate(ders, z);
    }
  }
}
