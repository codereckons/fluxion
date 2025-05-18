//======================================================================================================================
/*
  Kyosu - Hyperdual numbers
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <fluxion/details/callable.hpp>
#include <fluxion/details/compose.hpp>

namespace flx
{

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var gradient
//!   @brief Computes the gradient of a callable at an evaluation point.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <flx/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace flx
//!   {
//!      template<typename Func,  typename ... Xi> constexpr auto gradient(Func f, Xi const &... xi ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the kumi tuple containing the gradient components.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/differential.cpp}
//======================================================================================================================
//  inline constexpr auto differential = eve::functor<differential_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
// }

//   namespace flx::_
//   {

  template<typename Func, typename ... Xs>
  FLX_FORCEINLINE constexpr auto gradient(Func f, Xs const &... xs) noexcept
  {
    using v_t = decltype(f(flx::e0(xs)...));
    constexpr size_t S =  sizeof...(Xs);

    auto values = kumi::tuple{xs...};

    auto var_or_val = []<typename Pos, typename N>(Pos, N, auto x){
      if constexpr(Pos::value==N::value) return flx::variable<1>(x); else return x;
    };

    return [&]<std::size_t... N>(std::index_sequence<N...>)
    {
      using kumi::index;
      return kumi::tuple{ (flx::d1(kumi::apply( f
                                              , kumi::map_index( [&](auto idx, auto v)
                                                                 {
                                                                   return var_or_val(idx,index<N>, v);
                                                                 }
                                                               , values
                                                               )
                                              )))...};
    }(std::index_sequence_for<Xs...>{});

  }
}
