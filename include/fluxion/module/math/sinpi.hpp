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
#include <fluxion/details/mula.hpp>
#include <eve/module/math.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct sinpi_t : eve::elementwise_callable<sinpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sinpi_t, sinpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinpi
//!   @brief Computes the sinine of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT sinpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the sin of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinpi.cpp}
//======================================================================================================================
  inline constexpr auto sinpi = eve::functor<sinpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sinpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::sinpi(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sinpicospi(e0(z));
      auto pi = eve::pi(eve::as<b_t>());
      std::array<b_t, flx::max_order+1> ders{s, c, -s, -c, s};
      _::mul_by<flx::order_v<Z>>(ders, pi);
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
