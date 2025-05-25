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
#include <type_traits>
#include <array>

namespace flx
{
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
  //!     template < int  var,  int Order> constexér auto D(Func f)       noexcept;
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



  template<auto Vars,int Order>
  struct DD;

  template<std::size_t N>
  using vars = std::array<int,N>;

  template<std::size_t N, vars<N> Vars, int Order>
  struct DD<Vars, Order>
  {
    template<typename Func> constexpr auto operator()(Func f) noexcept
    {
      if constexpr(N == 1)
      {
        std::cout << "icitte0" << std::endl;
        std::cout << Vars[0]  << std::endl;
        std::cout << f(1.0, 2.0, 3.0) <<  std::endl;
        return [f](auto ... xi){
          return flx::e1(kumi::apply(f, flx::variable1<Vars[0]>(xi...)));
        };
      }
      else if constexpr(N == 2)
      {
        std::cout << "icitte1" << std::endl;
        std::cout << Vars[0] << "  " << Vars[1] << std::endl;
        std::cout << f(1.0, 2.0, 3.0) <<  std::endl;
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
      //return f;
    }
  };

  template<std::size_t I, int Order>
  struct DD<I, Order>
  {
    template<typename Func> constexpr auto operator()(Func f) noexcept
    {
      return [f](auto ... xi){
        return flx::e123(kumi::apply(f, flx::variable<I, Order>(xi...)));
      };
    }
  };


  template<auto ...Vars>
  struct DDD;

  template<std::size_t N, vars<N> Vars>
  struct DDD<Vars> : DD<Vars, N>
  {};

  template<std::size_t N, size_t Order>
  struct DDD<N, Order> : DD<N, Order>
  {};






//   template<int Order, auto vars> struct DD;

//   template<int I, int Ord> struct DD<I,Ord>
//   {
//     template<typename Func> constexpr auto operator()(Func f) noexcept
//     {
//       return [&](auto ... xi){
//         return flx::d<Ord>{}(kumi::apply(f, flx::variable1<I, Ord>(xi...)));
//       };
//     }
//   };

//   template<int N> using vars = std::array<int,N>;

//   template<int N, vars<N> Vars>
//   // requires(N <= 3) //For Now
//   struct DD<Vars, N>
//   {
//     template<typename Func> constexpr auto operator()(Func f) noexcept
//     {
//       if constexpr(N == 1)
//       {
//         return [&](auto ... xi){
//           return flx::e1(kumi::apply(f, variable1<Vars[0]>(xi...)));
//         };
//       }
//       else if constexpr(N == 2)
//       {
//         return [&](auto ... xi){
//           return flx::e12(kumi::apply(f, variable2<Vars[0], Vars[1]>(xi...)));
//         };
//       }
//       else if constexpr(N == 3)
//       {
//         return [&](auto ... xi){
//           return flx::e123(kumi::apply(f, variable3<Vars[0], Vars[1], Vars[2]>(xi...)));
//         };
//       }
//     }
//   };
}
