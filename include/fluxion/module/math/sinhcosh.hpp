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
#include <array>

namespace flx
{
  template<typename Options>
  struct sinhcosh_t : eve::callable<sinhcosh_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr  eve::zipped<Z, Z> operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sinhcosh_t, sinhcosh_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinhcos
//!   @brief Computes the sinh and cosh of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto sinhcos(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the sinh and cosh of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinhcosh.cpp}
//======================================================================================================================
  inline constexpr auto sinhcosh = eve::functor<sinhcosh_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sinhcosh_(flx_DELAY(), O const&, Z z) noexcept
  {
    using b_t = flx::as_base_type_t<Z>;
    auto [s, c] = eve::sinhcosh(e0(z));
    std::array<b_t, flx::max_order+1> derss{s, c, s, c, s};
    std::array<b_t, flx::max_order+1> dersc{c, s, c, s, c};
    return kumi::tuple{_::evaluate<order_v<Z>>(derss, z), _::evaluate<order_v<Z>>(dersc, z)};
  }
}
