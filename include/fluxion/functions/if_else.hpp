//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/functions/convert.hpp>
#include <fluxion/details/callable.hpp>

namespace flx
{
  template<typename Options>
  struct if_else_t : eve::callable<if_else_t, Options>
  {
    template<typename M, typename T, typename F>
    requires( concepts::hyperdual<T> || concepts::hyperdual<F>)
    FLX_FORCEINLINE constexpr expected_result_t<eve::if_else,M,T,F>
    operator()(M const& m, T const& t, F const& f) const noexcept
    {
      return flx_CALL(m,t,f);
    }

    template<typename M, typename T, typename F>
    FLX_FORCEINLINE constexpr auto
    operator()(M const& m, T const& t, F const& f) const noexcept -> decltype(eve::if_else(m,t,f))
    {
      return eve::if_else(m,t,f);
    }

    flx_CALLABLE_OBJECT(if_else_t, if_else_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var if_else
//!   @brief Select a value between two arguments based on a logical mask
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
//!     constexpr auto if_else(auto x, auto y, auto z ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: logical mask.
//!     * `y`, `z`: values to be selected.
//!
//!   **Return value**
//!
//!        elementwise `y` or `z` according the truth value of `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/if_else.cpp}
//======================================================================================================================
inline constexpr auto if_else = eve::functor<if_else_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}

namespace flx::_
{
  template<typename M, typename Z1, typename Z2, eve::callable_options O>
  FLX_FORCEINLINE constexpr auto if_else_(flx_DELAY(), O const& o, M const& m, Z1 const& t, Z2 const& f) noexcept
  {
    if constexpr(concepts::hyperdual<Z1> && concepts::hyperdual<Z2>)
    {
      using type  = as_hyperdual_t<Z1,Z2>;
      using ret_t = eve::as_wide_as_t<type,M>;

      return ret_t{ kumi::map ( [&](auto const& v, auto const& w) { return eve::if_else(m, v, w); }
                              , flx::convert(t, eve::as_element<type>{})
                              , flx::convert(f, eve::as_element<type>{})
                              )
                  };
    }
    else
    {
      auto parts = [&]()
      {
        auto cst = []<typename I>(auto x, I const&) { if constexpr(I::value == 0) return x; else return eve::zero; };

        if      constexpr(!concepts::hyperdual<Z2>)
          return kumi::map_index([&](auto i, auto e) { return eve::if_else(m, e, cst(f, i)); }, t);
        else if constexpr(!concepts::hyperdual<Z1>)
          return kumi::map_index([&](auto i, auto e) { return eve::if_else(m, cst(t, i), e); }, f);
      }();

      return eve::as_wide_as_t<std::conditional_t<!concepts::hyperdual<Z2>,Z1,Z2>,M>{parts};
    }
  }
}
