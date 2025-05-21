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

//   namespace flx::_
//   {

//   template<typename Func, typename ... Xs>
//   FLX_FORCEINLINE constexpr auto hessian(Func f, Xs const &... xs) noexcept
//   {
//     using v_t = decltype(f(flx::e0(xs)...));
//     constexpr size_t S =  sizeof...(Xs);

//     auto values = kumi::tuple{xs...};
//     if constexpr (S == 2)
//     {
//       return kumi::tuple{D2<0,0,1>(f)(xi...), D2<0,1,1>(f)(xi...), D2<1,0,1>(f)(xi...), D2<1,1,1>(f)(xi...)};
//     }
//     else
//     {
//       return kumi::tuple{}
//     }
//   }
// }


// template<int I, int J>
// auto D(auto func)
// {
//   return [func](auto... x) { std::cout << I << "," << J << "\n"; return func(x...); };
// }

  template<auto N>
  auto hessian(auto f)
  {
    auto as_index = kumi::generate<N>([](auto i) { return kumi::index<i>; });
    return kumi::map(   [&](auto e)
                        {
                          return kumi::apply([f](auto i, auto j) { return /*flx::D2<i,j, 1>(f)*/f; }, e);
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
                           constexpr size_t r = i % N;
                           constexpr size_t c = i / N;
                           that[r][c] = d(xn...);
                         }, h);

    return that;
  }
}
