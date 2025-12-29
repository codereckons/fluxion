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
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sqrt_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::sqrt(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto comp_ders = [&ders](auto  r){
        auto rz = eve::rec(r);
        using u_t = eve::underlying_type_t<b_t>;
        auto m = u_t(0.5);
        for(unsigned short i=1; (i <= flx::order_v<Z>); ++i, m -= 1)
        {
          ders[i] = ders[i-1]*rz*m;
        }
      };
      comp_ders(e0(z));
      return _::evaluate(ders, z);
    }
  }
}
