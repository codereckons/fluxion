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
  struct ceil_t : eve::elementwise_callable<ceil_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(ceil_t, ceil_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var ceil
//!   @brief Computes the ceil value of the parameter.
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
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> ceil(T z) noexcept;       // 1
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!    1. The  least integral value greater than z
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex ceil](https://en.cppreference.com/w/cpp/numeric/complex/ceil)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/ceil.cpp}
//======================================================================================================================
  inline constexpr auto ceil = eve::functor<ceil_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto ceil_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::ceil(e0(z));
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
