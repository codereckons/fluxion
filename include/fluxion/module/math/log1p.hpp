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
  struct log1p_t : eve::elementwise_callable<log1p_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(log1p_t, log1p_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var log1p
//!   @brief Computes the log1p of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT log1p(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the log1p of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/log1p.cpp}
//======================================================================================================================
  inline constexpr auto log1p = eve::functor<log1p_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
#include <span>

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto log1p_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::log1p(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto der = [](auto x){ return flx::rec(flx::inc(x)); };
      dersfromder<0, flx::order_v<Z>>(ders, der, e0(z));
      return _::evaluate(ders, z);
    }
  }
}
