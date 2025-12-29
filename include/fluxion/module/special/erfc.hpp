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
#include <eve/module/special.hpp>



namespace flx
{
  template<typename Options>
  struct erfc_t : eve::elementwise_callable<erfc_t, Options>
  {
    template<concepts::hyperdual_like Z>
    FLX_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return  flx_CALL(z);
    }

    flx_CALLABLE_OBJECT(erfc_t, erfc_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var erfc
//!   @brief Computes the complementary error function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <fluxion/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto erfc(floating_value auto x)   noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: argument.
//!
//!    **Return value**
//!
//!     The value of the complementary error function
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/erfc.cpp}
//======================================================================================================================
  inline constexpr auto erfc = eve::functor<erfc_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{

  template<typename Z, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto erfc_(flx_DELAY(), O const&, Z z) noexcept
  {
    auto val= eve::erfc(e0(z));
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      auto r = -flx::erf(z);
      e0(r) = val;
      return r;
    }
  }
}
