//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/scalar.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/same_lanes.hpp>
#include <eve/traits/element_type.hpp>
#include <type_traits>
#include <limits>

namespace flx::_
{
  constexpr unsigned short maxrank = std::numeric_limits<unsigned int>::max();
  template<typename T>                    inline constexpr unsigned int rank = 0;
  template<eve::floating_value T>         inline constexpr unsigned int rank<T> = maxrank;
  template<eve::integral_scalar_value T>  inline constexpr unsigned int rank<T> = maxrank;
  // rationale
  // hyperdual numbers of order M (rank 2^M) keep track of d�rivatives up to the Mth.
  // base field numbers keep the values of all derivatives as except for the order 0 (the value), they are all zero
}

namespace flx::concepts
{
  // Value of the Hyperdual  algebra encompass
  // actual real/complex values
  template<typename T>
  concept hyperdual_like = _::rank<std::remove_cvref_t<T>> != 0;

  template<typename T>
  concept dual_like = hyperdual_like<T> && _::rank<std::remove_cvref_t<T>> >= 2;

  template<typename T>
  concept dual2_like = hyperdual_like<T> && _::rank<std::remove_cvref_t<T>> >= 4;

  template<typename T>
  concept dual3_like = hyperdual_like<T> && _::rank<std::remove_cvref_t<T>> >= 8;

  /// General hyperdual concept
  template<typename T>
  concept hyperdual = hyperdual_like<T> && ( _::rank<std::remove_cvref_t<T>> > 1) && (_::rank<std::remove_cvref_t<T>> !=  _::maxrank);

  template<typename T>
  concept scalar_hyperdual = hyperdual<T> && eve::scalar_value<T>;

  /// General base concept
  template<typename T>
  concept base = hyperdual_like<T> && _::rank<std::remove_cvref_t<T>> == _::maxrank;

  template<typename T>
  concept scalar_base = base<T> && eve::scalar_value<T>;

  /// dual/dual1 number concept
  template<typename T>
  concept dual     = hyperdual<T> && _::rank<std::remove_cvref_t<T>> == 2;
  template<typename T>
  concept dual1    = hyperdual<T> && _::rank<std::remove_cvref_t<T>> == 2;

  /// dual2 concept
  template<typename T>
  concept dual2    = hyperdual<T> && _::rank<std::remove_cvref_t<T>> == 4;

  /// dual3 concept
  template<typename T>
  concept dual3    = hyperdual<T> && _::rank<std::remove_cvref_t<T>> == 8;
}
