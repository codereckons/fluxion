//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <eve/module/math.hpp>
#include <fluxion/details/mula.hpp>

namespace flx
{
  template<typename Options>
  struct exp2_t : eve::elementwise_callable<exp2_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(exp2_t, exp2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp2
//!   @brief Computes the base 2 exponential of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexp2r T exp2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the base 2 exponential of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp2.cpp}
//======================================================================================================================
  inline constexpr auto exp2 = eve::functor<exp2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto exp2_(flx_DELAY(), O const&, Z z) noexcept
  {
   if constexpr(concepts::base<Z>)
    {
      return eve::exp2(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto e = eve::exp2(e0(z));
      std::array<b_t, flx::max_order+1> ders{e, e, e, e, e};
      auto l2 = eve::log_2(eve::as<b_t>());
      _::mul_by<flx::order_v<Z>>(ders, l2);
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
