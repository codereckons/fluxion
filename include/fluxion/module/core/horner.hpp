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
  struct horner_t : eve::callable<horner_t, Options, pedantic_option>
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

    flx_CALLABLE_OBJECT(horner_t, horner_);
  };

//================================================================================================
//! @addtogroup functions
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials with coefficients
//!   in decreasing power order and its derivatives relative to x up to the order of the x hyperdual parameter.
//!
//!
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
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
//!      constexpr auto horner(floating_value auto x, value auto ...ci)                      noexcept; // 1
//!      constexpr auto horner(floating_value auto x, coefficients tci)                      noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto horner[pedantic](/*any of the above overloads*/)                     noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [evaluation point floating value](@ref eve::floating_value) arguments.
//!    * `ci...`: [floating values](@ref eve::floating_value) polynom coefficients in decreasing power order,
//!        Note that the values of the `ci` are not necessarily floating but the non floating ones
//!        are to be scalar
//!    * `tci`: [non empty tuple](@ref kumi::non_empty_product_type) of floating values.
//!
//!   **Return value**
//!
//!     If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!     power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
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
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Horner's_method)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/horner.cpp}
//================================================================================================
  inline constexpr auto horner = eve::functor<horner_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace flx::_
{
  template<typename X, typename C, typename... Cs, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto
  horner_(flx_DELAY(), O const & o, X xx, C c, Cs... cs) noexcept
  {
    using r_t  =  flx::as_hyperdual_like_t<X, C, Cs...>;
    if constexpr( sizeof...(Cs) == 0 ) return r_t(c);
    else
    {
      auto x = r_t(xx);
      r_t  that{0};
      that = fma[o](that, x, c);
      ((that = flx::fma[o](that, x, cs)), ...);
      return that;
    }
  }

  template<typename X, kumi::product_type Tuple, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto
  horner_(flx_DELAY(), O const & o, X x, eve::coefficients<Tuple> const& tup) noexcept
  {
    return kumi::apply( [&](auto... m) { return horner[o](x, m...); }, tup);
  }
}
