//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/functions/atan.hpp>
#include <eve/module/math.hpp>
namespace flx
{
  template<typename Options>
  struct pow_t : eve::strict_elementwise_callable<pow_t, Options, eve::raw_option>
  {
   template<concepts::hyperdual_like Z0, concepts::hyperdual_like Z1 >
    FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z0, Z1> operator()(Z0 c0, Z1 c1) const noexcept
    {
      return flx_CALL(c0, c1);
    }

//     template<concepts::hyperdual_like Z0, eve::integral_value Z1 >
//     FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z0, Z1> operator()(Z0 c0, Z1 c1) const noexcept
//     {
//       return flx_CALL(c0, c1);
//     }

    flx_CALLABLE_OBJECT(pow_t, pow_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var pow
//!   @brief Computes the  the pow operation \f$x^y\f$.
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
//!     // regular call
//!     constexpr auto pow(auto z0,  auto z1)  noexcept; //1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z0`, `z1`: Values to process.
//!
//!   **Return value**
//!
//!      Returns the  \f$z_0^z_1\f$.
//!
//!     Arguments can be a mix of floating and hyperdual values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/pow.cpp}
//======================================================================================================================
  inline constexpr auto pow = eve::functor<pow_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename Z1, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto pow_(flx_DELAY(), O const& o, Z0 x, Z1 y) noexcept
  {
    if constexpr(eve::integral_scalar_value<Z1>)
    {
      auto val = eve::pow[o](e0(x), y);
      using b_t = flx::as_base_type_t<Z0>;
      constexpr auto ord = flx::order_v<Z0>;
      std::array<b_t,ord+1> ders;
      ders[0] = val;
      auto rx = eve::rec(e0(x));
      auto comp_ders = [&](auto  x){
        ders[1] = val*y/x;
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = ders[1]*(y-1)/x;
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = ders[2]*(y-2)/x;
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = ders[3]*(y-3)/x;
              return;
            }
          }
        }
      };
      comp_ders(e0(x));
      return _::evaluate(ders, x);
    }
    else
    {
      auto val = eve::pow[o](e0(x), e0(y));
      if constexpr(concepts::base<Z0> && concepts::base<Z1>)
      {
        return val;
      }
      else
      {
        auto z = flx::exp(y*flx::log(x));
        e0(z) = val;
        return z;
      }
    }
  }
}
