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
  struct log2_t : eve::elementwise_callable<log2_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(log2_t, log2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log2
//!   @brief Computes the log2 of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT log2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the log2 of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log2.cpp}
//======================================================================================================================
  inline constexpr auto log2 = eve::functor<log2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
#include <span>

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto log2_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::log2(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      constexpr auto invlog_2 = eve::invlog_2(eve::as<eve::underlying_type_t<b_t>>()); ;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto der = [invlog_2](auto x){ return invlog_2*flx::rec(x); };
      dersfromder<0, flx::order_v<Z>>(ders, der, e0(z));
      return _::evaluate(ders, z);
    }
  }
}
