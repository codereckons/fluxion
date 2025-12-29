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
#include <fluxion/module/math/sech.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct gd_t : eve::elementwise_callable<gd_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(gd_t, gd_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var gd
//!   @brief Computes thegudermanian of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT gd(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns thegudermanian of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/gd.cpp}
//======================================================================================================================
  inline constexpr auto gd = eve::functor<gd_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto gd_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val= eve::gd(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto der = [](auto x){ return flx::sech(x); };
      dersfromder<0, flx::order_v<Z>>(ders, der, e0(z));
      for(int i=0; i <= flx::order_v<Z>; ++i)
      return _::evaluate(ders, z);
    }
  }
}
