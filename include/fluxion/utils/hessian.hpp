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
#include <fluxion/utils/derivatives.hpp>

namespace flx
{

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var gradient
//!   @brief Computes the hessian of a callable at an evaluation point.
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
//!     Returns the kumi tuple containing the hessian components.
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


  template<auto N>
  auto hessian(auto f)
  {
    auto as_index = kumi::generate<N>([](auto i) { return kumi::index<i>; });
    return kumi::map(   [&](auto e)
                        {
                          return kumi::apply([f](auto i, auto j) { return flx::D<flx::vars{static_cast<int>(i),static_cast<int>(j)}>{}(f); }, e);
                        }
                    ,   kumi::cartesian_product(as_index,as_index)
                    );
  }

  template<typename Func, typename ... T>
  auto hessian(Func f, T... xn)
  {
    constexpr size_t N = sizeof...(T);
    auto h = hessian<N>(f);

    std::array<std::array<decltype(f(xn...)),N>, N> that = {};
    kumi::for_each_index([&,f](auto i, auto d)
                         {
                           constexpr auto r = i % N;
                           constexpr auto c = static_cast<unsigned int>(i)/N;
                           if (r <= c)
                             that[r][c] = d(xn...);
                             that[c][r] = that[r][c];
                         }, h);

    return that;
  }
}
