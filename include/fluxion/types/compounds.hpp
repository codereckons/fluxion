//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/types/concepts.hpp>
#include <fluxion/module/core/if_else.hpp>
#include <fluxion/module/core/is_infinite.hpp>
#include <fluxion/module/core/is_eqz.hpp>
#include <fluxion/module/core/parts.hpp>
#include <fluxion/module/core/rec.hpp>
#include <iostream>

namespace flx
{
  //====================================================================================================================
  //! @name Compound Assignment Operators
  //! @related hyperdual
  //! @{
  //====================================================================================================================

  /// Adds the real value `other` to `self` and returns the new value of `self`.
  constexpr auto& operator+=(concepts::hyperdual auto& self, concepts::base auto other) noexcept
  requires( requires {get<0>(self) += other;} )
  {
    get<0>(self) += other;
    return self;
  }

  /// Adds the hyperdual value `other` to `self` and returns the new value of `self`.
  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> >= dimension_v<Self>)
  constexpr auto& operator+=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { get<I::value>(self) += o; }, other);
    return self;
  }

  /// Substracts the base value `other` from `self` and returns the new value of `self`.
  constexpr auto& operator-=(concepts::hyperdual auto& self, concepts::base auto other) noexcept
  requires( requires {get<0>(self) -= other;} )
  {
    get<0>(self) -= other;
    return self;
  }

  /// Substracts the hyperdual value `other` from `self` and returns the new value of `self`.
  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> >= dimension_v<Self>)
  constexpr auto& operator-=(Self& self, Other const& other) noexcept
  {
    kumi::for_each_index( [&]<typename I>(I,auto const& o) { get<I::value>(self) -= o; }, other);
    return self;
  }

  /// Multiplies `self` by the  base value `other`  and returns the new value of `self`.
  constexpr auto& operator*=(concepts::hyperdual auto& self, concepts::base auto other) noexcept
  requires( requires {get<0>(self) *= other;} )
  {
    kumi::for_each( [&](auto& s) { s *= other; }, self);
    return self;
  }

  /// Multiplies `self` by the hyperdual value `other`  and returns the new value of `self`.
  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> >= dimension_v<Self>)
  constexpr Self& operator*=(Self& self, Other const& other1) noexcept
  {
    Self other(other1);
    if constexpr(order_v<Self> == 1)
    {
      // dual is the floor state and need optimized handling with FMAs
      auto [ra,ia] = self;
      auto [rb,ib] = other;

      self = Self{ra*rb, eve::fma(ra,ib,ia*rb)};
    }
    else
    {
      constexpr auto ord = order_v<Self>-1;
      constexpr auto sz  = dimension_v<Self>/2;
      auto ria  = kumi::split(self ,kumi::index<sz>);
      auto rib  = kumi::split(other,kumi::index<sz>);

      using cd_t = as_hyperdual_n_t<ord, as_base_type_t<Self>>;
      cd_t  ra{get<0>(ria)}, ia{get<1>(ria)}
           , rb{get<0>(rib)}, ib{get<1>(rib)};
      // Hyperdual construction : (a,b) x  (c,d)= (a x b, d x a + b x c)
//       cd_t z0 = ra;  // TODO EST-CE MIEUX ??
//       z0 *= rb;
//       cd_t z1 = ra;
//       z1 *=  ib;
//       cd_t z2 = rb;
//       z2 *=  ia;
//       z1+= z2;
//       self = Self{kumi::cat(z0, z1)};

      // Hyperdual construction : (a,b) x  (c,d)= (a x b, d x a + b x c)
      self = Self{kumi::cat(ra * rb, ra*ib+rb*ia)};
    }
    return self;
  }

  /// Divides `self` by the  base value `other` and returns the new value of `self`.
  constexpr auto& operator/=(concepts::hyperdual auto& self, concepts::base auto other) noexcept
  requires( requires {get<0>(self) /= other;} )
  {
    if constexpr(eve::integral_scalar_value<decltype(other)>) //the rec of anint is problematic.
      kumi::for_each( [&](auto& s) { s /= other; }, self);
    else
    { auto ro =  eve::rec(other);
      kumi::for_each( [&](auto& s) { s *= ro; }, self);
    }
    return self;
  }

  /// Divides  `self` by the hyperdual value `other`  and returns the new value of `self`.
  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> >= dimension_v<Self>)
  constexpr Self& operator/=(Self& self, Other const& other) noexcept
  {
    return self *= flx::rec(other);
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
  //====================================================================================================================
  //  Requirements traps
  //  If a compilation error occurs and references one of those overloads, this means you tried to call an operator
  //  in an incorrect setup like:
  //    * compound assignment between a scalar and a wide (like Complex += Wide)
  //    * compound assignment between two hyperdual of incompatible dimension_v (like (dimension 4) += dimension 2 )
  //====================================================================================================================
#if !defined(FLUXION_DOXYGEN_INVOKED)
  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> <  dimension_v<Self>)
  constexpr auto& operator+=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator+=(concepts::hyperdual auto& self, concepts::base auto v) noexcept
  requires( !requires {get<0>(self) += v;} ) = delete;

  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> <  dimension_v<Self>)
  constexpr auto& operator-=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator-=(concepts::hyperdual auto& self, concepts::base auto v) noexcept
  requires( !requires {get<0>(self) -= v;} ) = delete;

  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> <  dimension_v<Self>)
  constexpr auto& operator*=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator*=(concepts::hyperdual auto& self, concepts::base auto v) noexcept
  requires( !requires {get<0>(self) *= v;} ) = delete;

  template<concepts::hyperdual Self, concepts::hyperdual Other>
  requires(dimension_v<Other> <  dimension_v<Self>)
  constexpr auto& operator/=(Self&, Other const&) noexcept = delete;

  constexpr auto& operator/=(concepts::hyperdual auto& self, concepts::base auto v) noexcept
  requires( !requires {get<0>(self) /= v;} ) = delete;
#endif
}
