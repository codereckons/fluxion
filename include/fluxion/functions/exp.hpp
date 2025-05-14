//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <eve/module/math.hpp>

namespace flx
{
  template<typename Options>
  struct exp_t : eve::elementwise_callable<exp_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(exp_t, exp_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var exp
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
//!      template<flx::concepts::hyperdual_like T> constexpr T exp(T z) noexcept;
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
//!  @godbolt{doc/exp.cpp}
//======================================================================================================================
  inline constexpr auto exp = eve::functor<exp_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto exp_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto b = eve::exp(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return b;
    }
    else if constexpr(flx::order_v<Z> == 1)
    {
      return Z(b, b*e1(z));
    }
    else if constexpr(flx::order_v<Z> == 2)
    {
      return  b*Z(1, e1(z), e2(z), e12(z)+e1(z)*e2(z));
    }
     else
    {
      using s_t =  as_base_type_t<Z>;
      auto pz = flx::pure(z);
      auto p1 = pz;
      Z p(1);
      s_t n(1);
      for(unsigned short i=1; i <= order_v<Z>; ++i)
      {
        n *= i;
        p += p1/n;
        p1 *= pz;
     }
      return p*b;
    }
  }
}
