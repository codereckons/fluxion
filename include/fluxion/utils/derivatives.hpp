//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright: FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/details/callable.hpp>
#include <fluxion/types/concepts.hpp>
#include <fluxion/types/traits.hpp>
#include <fluxion/functions/parts.hpp>
#include <fluxion/types/variables.hpp>

namespace flx
{
  template<std::size_t N>
  struct vars
  {
    constexpr int&  operator[](int i)       noexcept { return data[i]; }
    constexpr int   operator[](int i) const noexcept { return data[i]; }
    int data[N];
  };

  template<typename T, typename... U >
  vars(T, U... ) -> vars<1 + sizeof...(U)>;

  namespace _
  {
    template<auto Vars>
    struct D;

    template<std::size_t N, vars<N> Vars>
    struct D<Vars>
    {
      template<typename Func> constexpr auto operator()(Func f) const noexcept
      {
        if constexpr(N == 1)
        {
          return [f](auto ... xi){
            return flx::e1(kumi::apply(f, flx::variable1<Vars[0]>(xi...)));
          };
        }
        else if constexpr(N == 2)
        {
          return [f](auto ... xi){
            return flx::e12(kumi::apply(f, flx::variable2<Vars[0], Vars[1]>(xi...)));
          };
        }
        else if constexpr(N == 3)
        {
          return [f](auto ... xi){
            return flx::e123(kumi::apply(f, flx::variable3<Vars[0], Vars[1], Vars[2]>(xi...)));
          };
        }
      }
    };
  }

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var D
  //!   @brief return an invocable, the call of which returns the derivative relative
  //!   to a choice of variables of the function f
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
  //!     template < auto vars> constexpr auto D(Func f)       noexcept;
  //!     template < int  var,  int Order> constex�r auto D(Func f)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameters**
  //!
  //!   * `vars`: array of the indexes of the variables of derivation choosen (multiple occurences of the
  //!             same index implies mutiple derivations relative of this index.
  //!   * `Order`: order of derivation
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the callable \f$ (x_i) \leadsto \partial^N f}{\partial x_I^N} `.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/D.cpp}
  //====================================================================================================================
  template<auto Vars>
  inline constexpr auto D = _::D<Vars>{};

  template < int I,  unsigned short Order, typename Func,  typename ... Xs> constexpr auto
  derivate(Func f, Xs... xs) noexcept
  {
    return flx::d<Order>(kumi::apply(f, flx::variable<I, Order>(xs...)));
  }

  template < int I,  unsigned short Order, typename Func,  typename ... Xs> constexpr auto
  derivatives(Func f, Xs... xs) noexcept
  {
    using v_t = decltype(f(xs...));
    std::array<v_t, Order+1> that = {};
    auto hd = kumi::apply(f, flx::variable<I, Order>(xs...));
    kumi::for_each_index([&](auto i, auto )
                         {
                           if constexpr(i < Order+1) that[i] = d<i>(hd);
                         }, hd);
    return that;
  }




}
