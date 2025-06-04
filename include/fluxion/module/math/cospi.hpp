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
  struct cospi_t : eve::elementwise_callable<cospi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cospi_t, cospi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cospi
//!   @brief Computes the cosine of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT cospi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cos of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cospi.cpp}
//======================================================================================================================
  inline constexpr auto cospi = eve::functor<cospi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cospi_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::cospi(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sinpicospi(e0(z));
      auto pi = eve::pi(eve::as<b_t>());
      std::array<b_t, flx::max_order+1> ders{c, -s, -c, s, c};
      _::mul_by<flx::order_v<Z>>(ders, pi);
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
