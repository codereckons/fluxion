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
#include <fluxion/module/math/tan.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct cotpi_t : eve::elementwise_callable<cotpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(cotpi_t, cotpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var cotpi
//!   @brief Computes the cotangent of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT cotpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the cotangent of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/cotpi.cpp}
//======================================================================================================================
  inline constexpr auto cotpi = eve::functor<cotpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto cotpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::cotpi(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto pi = eve::pi(eve::as<eve::underlying_type_t<b_t>>());
      constexpr auto ord = flx::order_v<Z>;
      std::array<b_t,ord+1> ders;
      ders[0] = val;
      auto comp_ders = [&](auto  x){
        auto cscp2 = eve::sqr(eve::cscpi(x));
        ders[1] = -pi*cscp2;
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = 2*pi*pi*val*cscp2;
          if constexpr(ord == 2) return;
          else
          {
            auto val2 =  eve::sqr(val);
            auto pi2 = eve::pi2(eve::as<eve::underlying_type_t<b_t>>());
            ders[3] = -2*pi*pi2*cscp2*(2*val2+cscp2);
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = 8*eve::sqr(pi2)*val*cscp2*(val2+2*cscp2);
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
