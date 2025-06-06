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
  struct round_t : eve::elementwise_callable<round_t, Options, eve::upward_option, eve::downward_option,
                                eve::to_nearest_option, eve::toward_zero_option>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z z) const noexcept
    {
      return flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(round_t, round_);
  };

//======================================================================================================================
//! @addtogroup real
//! @{
//!   @var round
//!   @brief Computes the round value of the parameter.
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
//!      template<flx::concepts::hyperdual_like T> constexpr as_base_type_t<T> round(T z) noexcept;       // 1
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
//!   *  [C++ standard reference: complex round](https://en.cppreference.com/w/cpp/numeric/complex/round)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/round.cpp}
//======================================================================================================================
  inline constexpr auto round = eve::functor<round_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto round_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val = eve::round(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      auto r = flx::ceil(z); //the derivatives are always the same for all round options
      e0(r) = val;
      return r;
    }
  }
}
