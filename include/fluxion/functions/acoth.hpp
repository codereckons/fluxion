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
#include <fluxion/functions/log.hpp>
#include <fluxion/functions/inc.hpp>
#include <fluxion/functions/oneminus.hpp>
#include <array>

namespace flx
{
  template<typename Options>
  struct acoth_t : eve::elementwise_callable<acoth_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(acoth_t, acoth_);
};

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var acoth
//!   @brief Computes the arc cotangent of the argument.
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
//!      template<flx::concepts::hyperdual_like T> constexprT acoth(T z) noexcept;
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
//!  @groupheader{Example}
//!
//!  @godbolt{doc/acoth.cpp}
//======================================================================================================================
  inline constexpr auto acoth = eve::functor<acoth_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE FLX_FORCEINLINE constexpr auto acoth_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::acoth(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return eve::half(eve::as(e0(z)))*(flx::log(flx::inc(flx::rec(z)))-flx::log(flx::oneminus(flx::rec(z))));
    }
  }
}
