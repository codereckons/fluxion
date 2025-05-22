//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>
#include <eve/module/core.hpp>

namespace flx
{
  template<typename Options>
  struct abs_t : eve::elementwise_callable<abs_t, Options, eve::raw_option, internal_option>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(abs_t, abs_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var abs
//!   @brief Computes the absolute value of the parameter.
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
//!      //regular calls
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> abs(T z) noexcept;       // 1
//!
//!      // Semantic modifyiers
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> abs[raw](T z) noexcept;  // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    1. The  modulus of its parameter (always a floating ordered value).
//!       The modulus is the square root of the sum of the squares of the absolute value of each component.
//!    2. With the raw option no provision is made to enhance accuracy and avoid overflows
//!
//!   **Derivatives
//!
//!     - no derivative for complex based arguments
//!     - first derivative is sign(x)
//!     - other are all 0
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex abs](https://en.cppreference.com/w/cpp/numeric/complex/abs)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/abs.cpp}
//======================================================================================================================
  inline constexpr auto abs = eve::functor<abs_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto abs_(flx_DELAY(), O const& o, Z z) noexcept
  {
    if constexpr(O::contains(internal))
      return eve::maximum(eve::maxabs[o.drop(internal)](kumi::flatten(kumi::make_tuple(z))));
    else if constexpr(concepts::base<Z>)
    {
      return eve::abs[o](z);
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      b_t a= eve::abs(e0(z));
      b_t s = eve::signnz(e0(z));
      b_t zer(0);
      if constexpr(flx::order_v<Z> == 1)
      {
        return Z(a, s*e1(z));
      }
      else if constexpr(flx::order_v<Z> == 2)
      {
        return  Z(a, s*e1(z), s*e2(z), zer);
      }
      else
      {
        std::array<b_t, 5> ders{a, s, zer, zer, zer};
        return taylor(z, ders);
      }
    }
  }
}
