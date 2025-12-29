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
#include <eve/module/special.hpp>

namespace flx
{
  template<typename Options>
  struct erfcx_t : eve::elementwise_callable<erfcx_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(erfcx_t, erfcx_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto erfcx(floating_value auto x)   noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: argument.
//!
//!    **Return value**
//!
//!     The value of  the normalized complementary error function
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/erfcx.cpp}
//======================================================================================================================
  inline constexpr auto erfcx = eve::functor<erfcx_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto erfcx_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val= eve::erfcx(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      constexpr auto ord = flx::order_v<Z>;
      constexpr auto tosqtpi = eve::two_o_sqrt_pi(eve::as<eve::underlying_type_t<b_t>>()); ;
      std::array<b_t,flx::order_v<Z>+1> ders;
      ders[0] = val;
      auto comp_ders = [&](auto x){
        ders[1] = 2*x*ders[0]-tosqtpi;
        if constexpr(ord == 1) return;
        else
        {
          auto twox2 = 2*x*x;
          ders[2] = 2*ders[0]*flx::inc(twox2)-2*x*tosqtpi;
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = 4*ders[0]*x*(twox2+3)-tosqtpi*2*(twox2+2);
            if constexpr(ord == 3) return;
            else
            {
              ders[4] =4*ders[0]*(3+twox2*(6+twox2))-tosqtpi*4*x*(twox2+5);
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
