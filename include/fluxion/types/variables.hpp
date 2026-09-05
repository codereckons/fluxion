//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <fluxion/types/hyperdual.hpp>

#include <cstddef>
#include <utility>

namespace flx
{
  namespace _
  {
    // The seed of the argument sitting at position P: its value in the constant slot, a one in
    // front of every nilpotent unit that position is differentiated along, zero everywhere else.
    // Unit u lives at component 1 << u, so a component is a unit slot exactly when it holds a
    // single bit, and order_of reads which unit that is.
    template<std::size_t P, std::size_t... Is, typename T>
    [[nodiscard]]
    FLX_FORCEINLINE constexpr auto seed_of(T v) noexcept
    {
      constexpr std::size_t owner[] = {Is...};

      T                     o(1);
      T                     z(0);

      return [ & ]<std::size_t... C>(std::index_sequence<C...>)
      {
        return kumi::tuple {
            (C == 0 ? v : (std::has_single_bit(C) && owner[ order_of(C) ] == P ? o : z))...};
      }(std::make_index_sequence<1 << sizeof...(Is)> {});
    }

  }

  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //! @brief Turn a value into a variable of the given order
  //!
  //! The value goes in the constant slot and a one in front of each of the `Ord` nilpotent units,
  //! so that every derivative up to `Ord` flows from it. It is `hyperdual<T, Ord>{v, as_var{}}`
  //! with the type worked out rather than spelled, an order never being deducible from a value
  //! alone.
  //!
  //! @tparam Ord Order of derivation this variable carries
  //! @param  v   Value the variable takes
  //====================================================================================================================
  template<unsigned int Ord, concepts::base T>
    requires(Ord >= 1 && Ord <= max_order)
  [[nodiscard]]
  constexpr as_hyperdual_n_t<Ord, T> variable(T v) noexcept
  {
    auto d          = _::powersof2<Ord, T>();
    kumi::get<0>(d) = v;
    return as_hyperdual_n_t<Ord, T> {d};
  }

  //====================================================================================================================
  //! @brief Turn the arguments of a call into variables, each along the units it is differentiated
  //! by
  //!
  //! `Is...` is the list of derivations asked for, one entry per nilpotent unit: entry `u` names
  //! the argument that unit `u` belongs to. Its length is therefore the order, `variables<0, 0,
  //! 1>(x, y, z)` asking for two derivations in `x`, one in `y`, and none in `z`.
  //!
  //! Every argument named at least once comes back as a hyperdual seeded on its own units, every
  //! other one comes back untouched, at its own type, so the result feeds a call straight through
  //! `kumi::apply`.
  //!
  //! @tparam Is  Argument each unit is differentiated along, in unit order
  //! @param  xs  Arguments of the call
  //====================================================================================================================
  template<std::size_t... Is, concepts::base... Xs>
    requires(sizeof...(Is) >= 1 && sizeof...(Is) <= max_order && ((Is < sizeof...(Xs)) && ...))
  [[nodiscard]]
  constexpr auto variables(Xs... xs) noexcept
  {
    using r_t   = as_hyperdual_n_t<sizeof...(Is), Xs...>;
    using b_t   = as_base_type_t<r_t>;

    auto values = kumi::tuple {xs...};

    return [ & ]<std::size_t... P>(std::index_sequence<P...>)
    {
      return kumi::tuple {[ & ]<std::size_t Q>(kumi::index_t<Q>)
                          {
                            if constexpr(((Is == Q) || ...))
                              return r_t {_::seed_of<Q, Is...>(b_t(kumi::get<Q>(values)))};
                            else return kumi::get<Q>(values);
                          }(kumi::index<P>)...};
    }(std::index_sequence_for<Xs...> {});
  }

  //====================================================================================================================
  //! @}
  //====================================================================================================================
}
