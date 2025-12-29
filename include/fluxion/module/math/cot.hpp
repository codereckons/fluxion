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
#include <fluxion/module/math/tan.hpp>

namespace flx
{
  template<typename Options>
  struct cot_t : eve::elementwise_callable<cot_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cot_t, cot_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cot
//!   @brief Computes the cotangentt of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT cot(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the arc cotangent of the argument.
//!
//!   **Derivative values of order 1 to 4**
//!
//!     1. \f$-\csc^2(x)\f$
//!     2. \f$2 \cot(x) \csc^2(x)\f$
//!     3. \f$-2 (\csc^4(x) + 2 \cot^2(x) \csc^2(x))\f$
//!     4. \f$8 \cot(x) \csc^2(x) (\cot^2(x) + 2 \csc^2(x))\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cot.cpp}
//======================================================================================================================
  inline constexpr auto cot = eve::functor<cot_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cot_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::cot(e0(z));
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
      auto comp_ders = [&ders](auto  x){
        ders[1] = -eve::sqr(eve::csc(x));
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = -2*ders[0]*ders[1];
          if constexpr(ord == 2) return;
          else
          {
            ders[3] = 2*eve::fsm(eve::sqr(ders[1]), 2*eve::sqr(ders[0]), ders[1]);
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = -8*ders[0]*ders[1]*eve::fms(ders[0], ders[0], 2*ders[1]);
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
