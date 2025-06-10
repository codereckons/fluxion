//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <eve/module/math.hpp>

namespace flx
{
  template<typename Options>
  struct reverse_horner_t : eve::callable<reverse_horner_t, Options, pedantic_option>
  {
    template<concepts::hyperdual_like Z, concepts::base T, concepts::base ... Ts>
    //    requires(eve::same_lanes_or_scalar<Z, T, Ts...>)
    FLX_FORCEINLINE constexpr as_hyperdual_like_t<Z, T, Ts...>
    operator()(Z z, T t,  Ts...ts) const noexcept
    { return flx_CALL(z, t, ts...); }

    template<concepts::hyperdual_like Z, kumi::non_empty_product_type Tup>
    FLX_FORCEINLINE constexpr
    auto
    operator()(Z z, eve::coefficients<Tup> const& t) const noexcept
    { return EVE_DISPATCH_CALL(z, t); }

    flx_CALLABLE_OBJECT(reverse_horner_t, reverse_horner_);
  };

//================================================================================================
//! @addtogroup functions
//! @{
//!   @var reverse_horner
//!   @brief Implement the reverse_horner scheme to evaluate polynomials with coefficients
//!   in increasing power order and its derivatives relative to x up to the order of the x hyperdual parameter.
//!
//!
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!   power order,  the Reverse_Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!
//!   \f$\qquad\displaystyle p(x) = (((c_0x+c_1)x+ ... )x + c_{n-1})\f$
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto reverse_horner(floating_value auto x, value auto ...ci)                      noexcept; // 1
//!      constexpr auto reverse_horner(floating_value auto x, kumi::non_empty_product_type auto tci) noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto reverse_horner[pedantic](/*any of the above overloads*/)                     noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [evaluation point floating value](@ref eve::floating_value) arguments.
//!    * `ci...`: [floating values](@ref eve::floating_value) polynom coefficients in increasing power order,
//!        Note that the values of the `ci` are not necessarily floating but the non floating ones
//!        are to be scalar
//!    * `tci`: [non empty tuple](@ref kumi::non_empty_product_type) of floating values.
//!
//!   **Return value**
//!
//!     If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!     power order,  the Reverse_Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!     \f$\qquad\qquad\displaystyle p(x) = (((c_0x+c_1)x+ ... )x + c_{n-1})\f$
//!
//!     1. The value of the polynom at  `x` is returned.
//!     2. Same as the call with the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!     4. `fma[pedantic]` instead of `fma` is used in internal computations.
//!
//!    @note If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Reverse_Horner's_method)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/reverse_horner.cpp}
//================================================================================================
  inline constexpr auto reverse_horner = eve::functor<reverse_horner_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace flx::_
{
  template<typename X, typename C, typename... Cs, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto
  reverse_horner_(flx_DELAY(), O const & o, X x, C c0, Cs... cs) noexcept
  {
    kumi::tuple tup{c0, cs...};
    return  flx::horner[o](x, kumi::reverse(tup));
  }

  template<typename X, kumi::product_type Tuple, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto
  reverse_horner_(flx_DELAY(), O const & o, X x, eve::coefficients<Tuple>  tup) noexcept
  {
    return flx::horner[o](x, kumi::reverse(tup));
  }
}
