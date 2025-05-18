//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace flx
{

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var differential
//!   @brief Computes the differential of \f$f\f$ at \f$(z_i)_i\f$.
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
//!      template<typename Func,  typename ... Xi> constexpr auto differential(Func f, Xi const &... xi ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the invocable \f$( (dx_i...) \rightarrow \sum_i \frac{\partial f}{\partial x_i}|_(x_0, ...,  x_n)( (dx_0, ...,  dx_n))\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/differential.cpp}
//======================================================================================================================
//  inline constexpr auto differential = eve::functor<differential_t>;
//======================================================================================================================
//! @}
//======================================================================================================================

  template<typename Func, typename ... Zs>
  FLX_FORCEINLINE constexpr auto differential(Func f, Zs const &... xs) noexcept
  {
    {
      auto g = gradient(f, xs...);
      auto df = [g](auto const &... dxs){
        auto tdxs = kumi::tuple{dxs...};
        auto prod = [](auto l,  auto r){ return l*r; };
        return kumi::sum(kumi::map(prod, g, tdxs));
      };
      return df;
    }
  }
}
