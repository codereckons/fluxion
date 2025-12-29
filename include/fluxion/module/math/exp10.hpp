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
  struct exp10_t : eve::elementwise_callable<exp10_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(exp10_t, exp10_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp10
//!   @brief Computes the base 10 exponential of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexp10r T exp10(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the base 10 exponential of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp10.cpp}
//======================================================================================================================
  inline constexpr auto exp10 = eve::functor<exp10_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto exp10_(flx_DELAY(), O const&, Z z) noexcept
  {
   if constexpr(concepts::base<Z>)
    {
      return eve::exp10(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto e = eve::exp10(e0(z));
      std::array<b_t, flx::max_order+1> ders{e, e, e, e, e};
      auto l10 = eve::log_10(eve::as<b_t>());
      _::mul_by<flx::order_v<Z>>(ders, l10);
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
