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
  struct nthroot_t : eve::callable<nthroot_t, Options, eve::raw_option>
  {
//     template<concepts::hyperdual_like Z0, eve::integral_value U>
//     FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z0, U> operator()(Z0 c0, U n) const noexcept
//     {
//       return flx_CALL(c0, n);
//     }
    template<concepts::hyperdual_like Z0, concepts::hyperdual_like  U>
    FLX_FORCEINLINE constexpr auto/*as_hyperdual_like_t<Z0, U>*/ operator()(Z0 c0, U n) const noexcept
    {
      return flx_CALL(c0, n);
    }

    flx_CALLABLE_OBJECT(nthroot_t, nthroot_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var nthroot
//!   @brief Computes the  the nthroot operation \f$x^y\f$.
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
//!     constexpr auto nthroot(auto z0,  auto z1)  noexcept; //1
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
//!  @godbolt{doc/nthroot.cpp}
//======================================================================================================================
  inline constexpr auto nthroot = eve::functor<nthroot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z0, typename N, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto nthroot_(flx_DELAY(), O const& o, Z0 x, N n) noexcept
  {
    auto val = eve::nthroot[o](e0(x), e0(n));
    if constexpr(concepts::base<Z0>)
    {
      return val;
    }
    else
    {
      auto p =  n; //eve::convert(n,  eve::as(eve::element_type_t<Z0>()));
      using b_t = flx::as_base_type_t<Z0>;
      constexpr auto ord = flx::order_v<Z0>;
      std::array<b_t,ord+1> ders;
      ders[0] = val;
      auto rpx = eve::rec[pedantic](p*e0(x));
      auto comp_ders = [&](auto  x){
        ders[1] = val*rpx;
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = -ders[1]*(p-1)*rpx;
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = ders[2]*(2*p-1)*rpx;
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = -ders[3]*(3*p-1)*rpx;
              return;
            }
          }
        }
      };
      comp_ders(e0(x));
      return _::evaluate(ders, x);
    }
  }
}
