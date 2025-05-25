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
  //!   @brief return an invocable the call of which returns the derivative relative at the Ith variable of the function f of order N
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
  //!     template < unsigned short I, unsigned short N> constexpr auto D(Func f)       noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **template non type Parameters**
  //!
  //!   * `I`: index of the variable of derivation  from 0
  //!   * `N`: order of derivation
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

  template < auto I,  unsigned short Ord, typename Func> auto D(Func f) noexcept
  {
    return [&](auto ... xi){
      return flx::d<Ord>{}(kumi::apply(f, variable<I, Ord>(xi...))); //cor_value));
    };
  }
};
