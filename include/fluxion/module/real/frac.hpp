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
  struct frac_t : eve::elementwise_callable<frac_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(frac_t, frac_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var frac
//!   @brief Computes the frac value of the parameter.
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
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> frac(T z) noexcept;       // 1
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
//!   *  [C++ standard reference: complex frac](https://en.cppreference.com/w/cpp/numeric/complex/frac)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/frac.cpp}
//======================================================================================================================
  inline constexpr auto frac = eve::functor<frac_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto frac_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::frac(e0(z));
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
