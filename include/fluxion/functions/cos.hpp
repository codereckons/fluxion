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
  struct cos_t : eve::elementwise_callable<cos_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cos_t, cos_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cos
//!   @brief Computes the inverse of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT cos(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the inverse of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cos.cpp}
//======================================================================================================================
  inline constexpr auto cos = eve::functor<cos_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto cos_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::cos(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sincos(e0(z));
      if constexpr(flx::order_v<Z> == 1)
      {
        return Z(c, -s*e1(z));
      }
      else if constexpr(flx::order_v<Z> == 2)
      {
        return  Z(c, -s*e1(z), -s*e2(z), (-e12(z)*s-c*e1(z)*e2(z)));
      }
      else
      {
        std::array<b_t, flx::max_order+1> ders{c, -s, -c, s, c};
        return taylor(z, ders);
      }
    }
  }
}
