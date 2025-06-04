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
#include <array>

namespace flx
{
  template<typename Options>
  struct signnz_t : eve::callable<signnz_t, Options, eve::raw_option>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(signnz_t, signnz_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var signnz
//!   @brief Computes the signnz  value of the parameter.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/real.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signnzatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      //regular calls
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> signnz(T z) noexcept;       // 1
//!
//!      // Semantic modifyiers
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> signnz[raw](T z) noexcept;  // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    1. The  sign  of its parameter (always a floating ordered value).
//!    2. With the raw option no provision is made to enhance accuracy
//!
//!   **Derivatives
//!
//!     - no derivative for complex based arguments
//!     - first derivative is signnz(x)
//!     - other are all 0
//!
//!  @groupheader{Example}
//!  @godbolt{doc/signnz.cpp}
//======================================================================================================================
  inline constexpr auto signnz = eve::functor<signnz_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto signnz_(flx_DELAY(), O const& o, Z z) noexcept
  {
    using b_t = flx::as_base_type_t<Z>;
    auto a= eve::signnz[o](e0(z));
    if constexpr(concepts::base<Z>) return a;
    else
    {
      auto zer = eve::zero(eve::as(a));
      std::array<b_t, 5> ders{a, zer, zer, zer, zer};
      return _::evaluate<order_v<Z>>(ders, z);
    }
  }
}
