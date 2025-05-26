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
  struct chi_t : eve::callable<chi_t, Options>
  {
    template<concepts::hyperdual_like Z, concepts::base T1,  concepts::base T2>
    FLX_FORCEINLINE constexpr Z operator()(Z z, T1 lo,  T2 hi) const noexcept
    {
      return flx_CALL(z, lo, hi);
    }

    template<concepts::hyperdual_like Z, typename B >
    FLX_FORCEINLINE constexpr Z operator()(Z z, B belongs) const noexcept
    {
      return flx_CALL(z, belongs);
    }

    flx_CALLABLE_OBJECT(chi_t, chi_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var chi
//!   @brief Computes the chi value of the parameter.
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
//!      constexpr auto chi(auto x, value auto lo,  value auto hi)             noexcept; // 1
//!      constexpr auto chi(auto x, auto belongs)                              noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `z`: Value to process.
//!
//!   **Return value**
//!
//!
//!     * `x`: value to chi.
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) of the interval.
//!     * `belongs`: predicate function
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!        1. Each [element](@ref glossary_elementwise)  of the result contains:
//!           * `0`, if `x` is less than `lo`. or if `hi` is strictly less than `x`.
//!           * `1` otherwise.
//!        2  1 in the type of x if belongs(x) evaluate to true else 0.
//!        3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: complex chi](https://en.cppreference.com/w/cpp/numeric/complex/chi)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/chi.cpp}
//======================================================================================================================
  inline constexpr auto chi = eve::functor<chi_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename Z, typename T1,  typename T2, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto chi_(flx_DELAY(), O const&, Z z, T1 l, T2 h) noexcept
  {
    auto val = eve::chi(e0(z), l, h);
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto z(b_t(0));
      e0(z) = val;
      return z;
    }
  }

  template<typename Z, typename B, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto chi_(flx_DELAY(), O const&, Z z , B const & b) noexcept
  {
    auto val = eve::chi(e0(z), b);
    if constexpr(concepts::base<Z>)
    {
      return val;
    }
    else
    {
      using b_t = flx::as_base_type_t<Z>;
      auto z(b_t(0));
      e0(z) = val;
      return z;
    }
  }
}
