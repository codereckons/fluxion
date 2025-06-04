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
#include <fluxion/functions/tan.hpp>
#include <fluxion/functions/rec.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct tanpi_t : eve::elementwise_callable<tanpi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(tanpi_t, tanpi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var tanpi
//!   @brief Computes the tanangent of the argument from an input in \f$\pi\f$ multiples..
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
//!      template<flx::concepts::hyperdual_like T> constexprT tanpi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the tanangent of the argument from an input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/tanpi.cpp}
//======================================================================================================================
  inline constexpr auto tanpi = eve::functor<tanpi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto tanpi_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::tanpi(e0(z));
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
        auto secp2 = eve::sqr(eve::secpi(x));
        ders[1] = pi*secp2;
        if constexpr(ord == 1) return;
        else
        {
          ders[2] = 2*pi*pi*val*secp2;
          if constexpr(ord == 2) return;
          else
          {
            auto val2 =  eve::sqr(val);
            auto pi2 = eve::pi2(eve::as<eve::underlying_type_t<b_t>>());
            ders[3] = 2*pi*pi2*secp2*(2*val2+secp2);
            if constexpr(ord == 3) return;
            else
            {
              ders[4] = 8*eve::sqr(pi2)*val*secp2*(val2+2*secp2);
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
