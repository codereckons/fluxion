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
  struct secpi_t : eve::elementwise_callable<secpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(secpi_t, secpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var secpi
//!   @brief Computes the secant of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT secpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the secant of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/secpi.cpp}
//======================================================================================================================
  inline constexpr auto secpi = eve::functor<secpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto secpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::secpi(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto pi = eve::pi(eve::as<eve::underlying_type_t<b_t>>());

      auto r = flx::sec(pi*z);
      e0(r) = val;
      return r;
    }
  }
}
