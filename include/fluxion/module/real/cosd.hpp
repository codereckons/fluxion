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
  struct cosd_t : eve::elementwise_callable<cosd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cosd_t, cosd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cosd
//!   @brief Computes the cosdine of the argument from an input in degrees..
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
//!      template<flx::concepts::hyperdual_like T> constexprT cosd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cosd of the argument from an input in degrees.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cosd.cpp}
//======================================================================================================================
  inline constexpr auto cosd = eve::functor<cosd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cosd_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::cosd(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sindcosd(e0(z));
      auto deg(1.745329251994330e-02);
      std::array<b_t, flx::max_order+1> ders{c, -s, -c, s, c};
      _::mul_by<flx::order_v<Z>>(ders, deg);
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
