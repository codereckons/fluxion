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
  struct sin_t : eve::elementwise_callable<sin_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sin_t, sin_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sin
//!   @brief Computes the sine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT sin(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the sine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sin.cpp}
//======================================================================================================================
  inline constexpr auto sin = eve::functor<sin_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sin_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::sin(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto [s, c] = eve::sincos(e0(z));
      if constexpr(flx::order_v<Z> == 1)
      {
        return chain(z, s, c);
      }
      else if constexpr(flx::order_v<Z> == 2)
      {
        return  chain(z, s, c, -s);
      }
      else
      {
        std::array<b_t, flx::max_order+1> ders{s, c, -s, -c, s};
        return taylor(z, ders);
      }
    }
  }
}
