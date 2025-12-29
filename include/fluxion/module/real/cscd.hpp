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
  struct cscd_t : eve::elementwise_callable<cscd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cscd_t, cscd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cscd
//!   @brief Computes the cosecant of the argument from an input in degrees.
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
//!      template<flx::concepts::hyperdual_like T> constexprT cscd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosecant of the argument from an input in degrees.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cscd.cpp}
//======================================================================================================================
  inline constexpr auto cscd = eve::functor<cscd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cscd_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::cscd(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto deg(1.745329251994330e-02);
      auto r = flx::csc(deg*z);
      e0(r) = val;
      return r;
    }
  }
}
