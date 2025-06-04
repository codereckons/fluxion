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
  struct sign_t : eve::elementwise_callable<sign_t, Options, eve::raw_option>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sign_t, sign_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var sign
//!   @brief Computes the signolute value of the parameter.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      //regular calls
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> sign(T z) noexcept;       // 1
//!
//!      // Semantic modifyiers
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> sign[raw](T z) noexcept;  // 2
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
//!       The modulus is the square root of the sum of the squares of the signolute value of each component.
//!    2. With the raw option no provision is made to enhance accuracy and avoid overflows
//!
//!   **Derivatives
//!
//!     - no derivative for complex based arguments
//!     - first derivative is sign(x)
//!     - other are all 0
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex sign](https://en.cppreference.com/w/cpp/numeric/complex/sign)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/sign.cpp}
//======================================================================================================================
  inline constexpr auto sign = eve::functor<sign_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sign_(flx_DELAY(), O const& o, Z z) noexcept
  {
    using b_t = flx::as_base_type_t<Z>;
    auto a= eve::sign[o](e0(z));
    if constexpr(concepts::base<Z>) return a;
    else
    {
      auto zer = eve::zero(eve::as(a));
      std::array<b_t, 5> ders{a, zer, zer, zer, zer};
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
