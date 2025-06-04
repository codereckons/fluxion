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
  struct cosh_t : eve::elementwise_callable<cosh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cosh_t, cosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cosh
//!   @brief Computes the hyperbolic cosine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT cosh(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the hyperbolic cosine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cosh.cpp}
//======================================================================================================================
  inline constexpr auto cosh = eve::functor<cosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cosh_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::cosh(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sinhcosh(e0(z));
      std::array<b_t, flx::max_order+1> ders{c, s, c, s, c};
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
