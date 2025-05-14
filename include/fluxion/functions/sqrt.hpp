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

namespace flx
{
  template<typename Options>
  struct sqrt_t : eve::elementwise_callable<sqrt_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sqrt_t, sqrt_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sqrt
//!   @brief Computes the square root of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr T sqrt(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the square root of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sqrt.cpp}
//======================================================================================================================
  inline constexpr auto sqrt = eve::functor<sqrt_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template <typename T> FLX_FORCEINLINE auto sqrt_ders(T const & z) noexcept
  {
    using b_t = flx::as_base_type_t<T>;
    using u_t = eve::underlying_type_t<b_t>;
    std::array<b_t, flx::order_v<T>+1> ders{};
    const auto e0z = e0(z);
    ders[0] = eve::sqrt(e0z);
    auto rz = eve::rec(e0z);
    auto m = u_t(0.5);
    for(unsigned short i=1; (i <= flx::order_v<T>) && eve::is_nez(m); ++i, m -= 1)
    {
      ders[i] = ders[i-1]*rz*m;
    }
    return ders;
  }

  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto sqrt_(flx_DELAY(), O const&, Z z) noexcept
  {
    if constexpr(concepts::base<Z>)
    {
      return eve::sqrt(z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      using u_t = eve::underlying_type_t<b_t>;
      auto sq0  = eve::sqrt(e0(z));
      auto hrsq0 = u_t(0.5)*eve::rec(sq0);
      if constexpr(flx::order_v<Z> == 1)
      {
        return Z(sq0, hrsq0*e1(z));
      }
      else
      {
        auto ders = sqrt_ders(z);
        return taylor(z, ders);
      }
    }
  }
}
