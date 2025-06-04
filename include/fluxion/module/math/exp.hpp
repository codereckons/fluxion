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

namespace flx
{
  template<typename Options>
  struct exp_t : eve::elementwise_callable<exp_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(exp_t, exp_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp
//!   @brief Computes the exponential of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T exp(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the exponential of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/exp.cpp}
//======================================================================================================================
  inline constexpr auto exp = eve::functor<exp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto exp_(flx_DELAY(), O const&, Z z) noexcept
  {
   if constexpr(concepts::base<Z>)
    {
      return eve::exp(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto e = eve::exp(e0(z));
      std::array<b_t, flx::max_order+1> ders{e, e, e, e, e};
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
