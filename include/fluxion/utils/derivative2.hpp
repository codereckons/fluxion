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
#include <type_traits>

namespace flx
{
  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var D
  //!   @brief return an invocable the call of which returns the derivative relative
  //!   at the Ith and Jth variables of the callable f
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
  //!     template < unsigned short I, unsigned short J> constexpr auto D2(Func f)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameters**
  //!
  //!   * `I`: index of the first variable of derivation from 0
  //!   * `J`: index of the second variable of derivation from 0
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     Returns the callable \f$ (x_i) \leadsto \partial^2 f}{\partial x_I\partial x_J} `.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/D2.cpp}
  //====================================================================================================================

  template < auto I, auto J, typename Func> auto D2(Func f) noexcept
  {
    return [&](auto ... xi){
      return flx::e12(kumi::apply(f, variable2<I, J>(xi...)));
    };
  }
};
