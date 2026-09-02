//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/eve.hpp>
#include <fluxion/details/abi.hpp>
#include <fluxion/types/concepts.hpp>
#include <fluxion/types/traits.hpp>
#include <bit>

namespace flx
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //====================================================================================================================

  namespace _
  {
    // The seed of a variable: a one at every index that is a power of two, the single unit slots,
    // and zero elsewhere.
    template<std::size_t Order, typename T>
    [[nodiscard]]
    FLX_FORCEINLINE constexpr auto powersof2() noexcept
    {
      T z(0);
      T o(1);
      return [ & ]<std::size_t... I>(std::index_sequence<I...>)
      {
        return kumi::tuple {(std::has_single_bit(I) ? o : z)...};
      }(std::make_index_sequence<1 << Order> {});
    }

  }

  //! @brief Tag requesting a variable rather than a constant
  //!
  //! Passed beside the value, it seeds a one in front of each nilpotent unit, which is what makes
  //! the derivatives flow from that argument.
  struct as_var
  {
  };

  /// The tag instance, ready to pass
  inline constexpr as_var var = {};

  //====================================================================================================================
  //! @class hyperdual
  //! @brief hyperdual numbers main abstraction
  //! It is built so that all operations can be done in a streamlined fashion
  //====================================================================================================================
  template<concepts::scalar_base Type, unsigned int Ord>
    requires(Ord >= 1 && Ord <= 4)
  struct hyperdual
  {
    using underlying_type                          = Type;
    using is_hyperdual                             = void;

    static constexpr unsigned int static_dimension = 1 << Ord;
    static constexpr unsigned int order            = Ord;

    /// Default hyperdual constructor
    constexpr hyperdual() noexcept
        : contents {}
    {
    }

    /// Construct a hyperdual constant from a base value
    template<std::convertible_to<Type> T>
    constexpr hyperdual(T v) noexcept
        : contents {}
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a hyperdual variable from a base value
    template<std::convertible_to<Type> T>
    constexpr hyperdual(T v, as_var) noexcept
        : contents(_::powersof2<order, Type>())
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a hyperdual instance from a sequences of base values
    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
      requires((sizeof...(Ts)) >= static_dimension)
    constexpr hyperdual(T0 v0, Ts... vs) noexcept
        : contents {kumi::extract(kumi::tuple {static_cast<Type>(v0), static_cast<Type>(vs)...},
                                  kumi::index<0>,
                                  kumi::index<static_dimension>)}
    {
    }

    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
      requires((1 + sizeof...(Ts)) == static_dimension)
    constexpr hyperdual(T0 v0, Ts... vs) noexcept
        : contents {static_cast<Type>(v0), static_cast<Type>(vs)...}
    {
    }

    /// Construct a hyperdual instance from a properly sized product_type
    constexpr hyperdual(eve::sized_product_type<static_dimension> auto const& vs)
        : contents {vs}
    {
    }

    /// Constructs a hyperdual instance from an hyperdual of greater order
    template<unsigned int M>
      requires(M >= order)
    constexpr hyperdual(hyperdual<Type, M> const& a) noexcept
        : contents(kumi::extract(a.contents, kumi::index<0>, kumi::index<static_dimension>))
    {
    }

    /// Assign a greater order hyperdual to another
    template<concepts::hyperdual T>
    constexpr hyperdual& operator=(T const& a) noexcept
      requires(T::static_dimension > static_dimension)
    {
      return (*this = hyperdual {kumi::extract(a, kumi::index<0>, kumi::index<static_dimension>)});
    }

    //==================================================================================================================
    // ++/--
    //==================================================================================================================

    //! Pre-incrementation operator
    FLX_FORCEINLINE auto& operator++() noexcept
    {
      kumi::get<0>(contents)++;
      return *this;
    }

    //! Pre-decrementation operator
    FLX_FORCEINLINE auto& operator--() noexcept
    {
      kumi::get<0>(contents)--;
      return *this;
    }

    //! Post-incrementation operator
    FLX_FORCEINLINE auto operator++(int) noexcept
    {
      auto that(*this);
      this->operator++();
      return that;
    }

    //! Post-decrementation operator
    FLX_FORCEINLINE auto operator--(int) noexcept
    {
      auto that(*this);
      this->operator--();
      return that;
    }

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type       = kumi::result::fill_t<static_dimension, Type>;
    using is_product_type = void;

    friend constexpr eve::as_logical_t<Type> operator==(hyperdual const& a,
                                                        hyperdual const& b) noexcept
    {
      return get<0>(a.contents) == get<0>(b.contents);
    }

    friend constexpr eve::as_logical_t<Type> operator!=(hyperdual const& a,
                                                        hyperdual const& b) noexcept
    {
      return get<0>(a.contents) != get<0>(b.contents);
    }

    data_type contents;
  };

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //! @brief Access the Ith component of a hyperdual
  //!
  //! The layout is binary: bit i of I set means the component carries the nilpotent unit i, so
  //! index zero is the value and the indices that are powers of two are the first order parts.
  template<std::size_t I, typename T, unsigned int N>
  constexpr auto& get(hyperdual<T, N>& c) noexcept
  {
    return kumi::get<I>(c.contents);
  }

  template<std::size_t I, typename T, unsigned int N>
  constexpr auto get(hyperdual<T, N> const& c) noexcept
  {
    return kumi::get<I>(c.contents);
  }

  //====================================================================================================================
  //! @name Deduction Guides
  //! @related hyperdual
  //! @{
  //====================================================================================================================
  /// Deduction guide for constructing from product type
  template<eve::product_type Tuple>
  hyperdual(Tuple const&) -> hyperdual<kumi::element_t<0, Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  hyperdual(T0, Ts...) -> hyperdual<T0, 1 + sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================

  /// create a hyperdual variable from a base value
  template<unsigned int Order, concepts::base T>
  constexpr as_hyperdual_n_t<Order, T> variable(T v) noexcept
  {
    using r_t       = as_hyperdual_n_t<Order, T>;
    auto d          = _::powersof2<Order, T>();
    kumi::get<0>(d) = v;
    r_t hv(d);
    return hv;
  }

}

namespace flx::_
{
  // What the concepts read: the component count of a hyperdual, seen through a wide as well.
  template<typename T, unsigned int Order>
  inline constexpr unsigned int rank<hyperdual<T, Order>> = 1 << Order;

  template<typename T, unsigned int Order, typename L>
  inline constexpr unsigned int rank<eve::wide<hyperdual<T, Order>, L>> = 1 << Order;
}

#if !defined(flx_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned int Order>
struct std::tuple_size<flx::hyperdual<T, Order>> : std::integral_constant<std::size_t, 1 << Order>
{
};

template<typename T, unsigned int Order, std::size_t I>
struct std::tuple_element<I, flx::hyperdual<T, Order>>
{
  using type = T;
};

#endif

#include <fluxion/types/io.hpp>
// compounds.hpp and operators.hpp return with the operations step: they pull module/core in.
