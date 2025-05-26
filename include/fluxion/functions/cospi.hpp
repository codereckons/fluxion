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
      if constexpr(flx::order_v<Z> == 1)
      {
        return Z(c, -s*pi*e1(z));
      }
      else if constexpr(flx::order_v<Z> == 2)
      {
        return  Z(c, -s*pie1(z), -s*pie2(z), pi*pi(-e12(z)*s-c*e1(z)*e2(z)));
      }
      else
      {
        std::array<b_t, flx::max_order+1> ders{c, -s*pi, -c*pi*pi, s*pi*pi*pi, c*pi*pi*pi*pi};
        return taylor(z, ders);
      }
    }
  }
}
