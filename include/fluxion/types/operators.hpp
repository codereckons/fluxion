//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/types/compounds.hpp>
#include <fluxion/functions/convert.hpp>
#include <fluxion/functions/rec.hpp>
#include <fluxion/functions/is_equal.hpp>

namespace flx
{
  //====================================================================================================================
  //! @name Unary Operators
  //! @{
  //====================================================================================================================

  //! @brief Identity for Hyperdual value
  //! @related hyperdual
  template<concepts::hyperdual Z>
  constexpr auto operator+(Z const& z) noexcept
  {
    return z;
  }

  //! @brief Compute the negation of a given Hyperdual value
  //! @related hyperdual
  template<concepts::hyperdual Z>
  constexpr auto operator-(Z const& z) noexcept
  {
    return Z{kumi::map([](auto m) { return -m; }, z)};
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //====================================================================================================================
  //! @name Binary Operators
  //! @{
  //====================================================================================================================

  //! @brief Returns the sum of two hyperdual values in any order
  //! @related hyperdual

  template<typename T1,  typename T2>
  as_hyperdual_t<T1,T2> operator+(T1 const & a, T2 const & b) noexcept
  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  {
    if constexpr(!concepts::hyperdual<T1>) return b + a;
    else
    {
      using type = as_hyperdual_t<T1,T2>;
      type that{flx::convert(a,eve::as<eve::element_type_t<type>>())};
      return that += b;
    }
  }

  //! @brief  Returns the difference of two hyperdual values
  //! @related hyperdual
  template<eve::value T1, eve::value T2>
  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  as_hyperdual_t<T1,T2> operator-(T1 const& a, T2 const& b) noexcept
  {
    if constexpr(!concepts::hyperdual<T1>) return (-b)+a;
    else
    {
      using type = as_hyperdual_t<T1,T2>;
      type that{flx::convert(a,eve::as<eve::element_type_t<type>>())};
      return that -= b;
    }
  }

  //! @brief Returns the product of two hyperdual values
  //! @related hyperdual
  template<eve::value T1, eve::value T2>
  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  as_hyperdual_t<T1,T2> operator*(T1 const& a, T2 const& b) noexcept
  {
    if constexpr(!concepts::hyperdual<T1>) return b*a;
    else
    {
      using type = as_hyperdual_t<T1,T2>;
      type that{flx::convert(a,eve::as<eve::element_type_t<type>>())};
      return that *= b;
    }
  }

  //! @brief Returns the ratio of two hyperdual values
  //! @related hyperdual
  template<eve::value T1, eve::value T2>
  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  as_hyperdual_t<T1,T2> operator/(T1  a, T2  b) noexcept
  {
    if constexpr(!concepts::hyperdual<T1>){
      return flx::rec(b)*a;
    }
    else if constexpr(!concepts::hyperdual<T2>)
    {
      if constexpr(eve::integral_scalar_value<T2>)
        return a /= b; // so conversion is taken into  account
      else
        return a*eve::rec(b);
    }
    else
    {
      return a*flx::rec(b);
    }
  }

  //! @brief Compares two hyperdual values for equality
  //! @related hyperdual
  template<concepts::hyperdual_like T1, concepts::hyperdual_like T2>
  //  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  constexpr auto operator==( T1 const& a, T2  const& b)
  {
    std::cout << "icitte" << std::endl;
    return flx::is_equal(a, b);
   return e0(a) == e0(b);
  }

  //! @brief Compares  two hyperdual values for inequality
  //! @related hyperdual
  template<concepts::hyperdual_like T1, concepts::hyperdual_like T2>
  //  requires(concepts::hyperdual<T1> || concepts::hyperdual<T2>)
  constexpr auto operator!=( T1 const& a, T2 b)
  {
    return e0(a) != e0(b);
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
