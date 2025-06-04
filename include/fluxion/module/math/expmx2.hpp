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
#include <fluxion/details/mula.hpp>

namespace flx
{
  template<typename Options>
  struct expmx2_t : eve::elementwise_callable<expmx2_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(expmx2_t, expmx2_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var expmx2
//!   @brief Computes the  exponential of the opposite of the squared argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpmx2r T expmx2(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the base 2 exponential of the opposite of the squared argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/expmx2.cpp}
//======================================================================================================================
  inline constexpr auto expmx2 = eve::functor<expmx2_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
   FLX_FORCEINLINE constexpr auto expmx2_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val =eve::expmx2(e0(z));
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
        ders[1] =  -2*x*val;
        if constexpr(ord == 1) return;
        else
        {
          auto x2 = x*x;
          ders[2] = 2*val*(2*x2-1);
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = -4*val*x*(2*x2-3);
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = 4*val*(3+x2*(-12+4*x2));
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
