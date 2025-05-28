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
#include <array>

namespace flx
{

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var laplacian
//!   @brief Computes the laplacian of a callable at an evaluation point.
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
//!      template<typename Func,  typename ... Xi> constexpr auto laplacian(Func f, Xi const &... xi ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z`: Value to process.
//!
//!   **Return value**
//!
//!     Returns the laplacian value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/laplacian.cpp}
//======================================================================================================================
//  inline constexpr auto differential = eve::functor<differential_t>;
//======================================================================================================================
//! @}
//======================================================================================================================

  template<typename ... Xn>
  auto laplacian(auto f, Xn... xn)
  {
    constexpr size_t N = sizeof...(Xn);
    return kumi::sum(kumi::map([&](auto e) { return D<vars{e, e}>(f)(xn...); }
                              ,   kumi::generate<N>([](auto i) { return kumi::index<i>; })
                              )
                    );
  }
  
}
