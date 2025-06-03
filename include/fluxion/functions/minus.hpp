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
  struct minus_t : eve::elementwise_callable<minus_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(minus_t, minus_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var minus
//!   @brief Computes the opposite value.
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
//!      template<flx::concepts::hyperdual_like T> T minus(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    1. -z
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex minus](https://en.cppreference.com/w/cpp/numeric/complex/minus)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/minus.cpp}
//======================================================================================================================
  inline constexpr auto minus = eve::functor<minus_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto minus_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::minus(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      return Z(val);
    }
  }
}
