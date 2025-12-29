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
  struct sinhc_t : eve::elementwise_callable<sinhc_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sinhc_t, sinhc_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinhc
//!   @brief Computes the cardinal sine of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT sinhc(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cardinal sine of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinhc.cpp}
//======================================================================================================================
  inline constexpr auto sinhc = eve::functor<sinhc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sinhc_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::sinhc(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      constexpr auto ord = flx::order_v<Z>;
      std::array<b_t,ord+1> ders;
      ders[0] = val;
      auto comp_ders = [&](auto  x){
        auto [s, c] = eve::sinhcosh(e0(z));
        auto rx =  eve::rec(x);
        auto rx2 = eve::sqr(rx);
        auto test = (eve::abs(e0(z)) < eve::eps(as<b_t>()));
        ders[1] = if_else(test, eve::zero, eve::fms(x, c, s)*rx2);
        if constexpr(ord == 1) return;
        else
        {
          auto x2 = eve::sqr(x);
          ders[2] =  if_else(test, eve::third(eve::as(val)), eve::fnma(2*x, c, (x2+2)*s)*rx2*rx);
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = if_else(test, eve::zero,  eve::fnma(3*(x2+2), s, x*(x2+6)*c)*eve::sqr(rx2));
            if constexpr(ord == 3) return;
            else
            {
              ders[4] =if_else(test, b_t(1.0/5),  eve::fnma(4*x*(x2+6), c, (24+x2*(x2+12))*s)*eve::sqr(rx2)*rx);
              return;
            }
          }
        }
      };
      comp_ders(e0(z));
      return _::evaluate(ders, z);
    }
  }
}
