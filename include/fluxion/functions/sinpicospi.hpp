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
  struct sinpicospi_t : eve::elementwise_callable<sinpicospi_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr  eve::zipped<Z, Z> operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(sinpicospi_t, sinpicospi_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var sinpicospi
//!   @brief Computes the sin and cos of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexpr auto sinpicospi(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the sin and cos of the argument.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/sinpicospi.cpp}
//======================================================================================================================
  inline constexpr auto sinpicospi = eve::functor<sinpicospi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}


namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto sinpicospi_(flx_DELAY(), O const&, Z z) noexcept
  {
    using b_t = flx::as_base_type_t<Z>;
    auto [s, c] = eve::sinpicospi(e0(z));
    std::array<b_t, flx::max_order+1> derss{s, c, -s, -c, s};
    std::array<b_t, flx::max_order+1> dersc{c, -s, -c, s, c};
    auto pi = eve::pi(eve::as<b_t>());
    _::mul_by<flx::order_v<Z>>(derss, pi);
    _::mul_by<flx::order_v<Z>>(dersc, pi);
    return kumi::tuple{_::evaluate<order_v<Z>>(derss, z), _::evaluate<order_v<Z>>(dersc, z)};
  }
}
