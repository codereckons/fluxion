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
  struct cscpi_t : eve::elementwise_callable<cscpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cscpi_t, cscpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cscpi
//!   @brief Computes the cosecant of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT cscpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosecant of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cscpi.cpp}
//======================================================================================================================
  inline constexpr auto cscpi = eve::functor<cscpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cscpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::cscpi(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto pi = eve::pi(eve::as<eve::underlying_type_t<b_t>>());

      auto r = flx::csc(pi*z);
      e0(r) = val;
      return r;
    }
  }
}
