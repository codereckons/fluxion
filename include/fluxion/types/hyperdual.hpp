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
#include <iostream>

namespace flx
{
  //====================================================================================================================
  //! @addtogroup types
  //! @{
  //====================================================================================================================

  namespace _
  {
    template<std::size_t Order, typename T> [[nodiscard]]
    FLX_FORCEINLINE constexpr auto powersof2() noexcept
    {
      T z(0);
      T o(1);
//       auto gen = [o, z](auto i){
//         return std::has_single_bit(i) ? o : z;
//     };
//      return kumi::generate<1 << Order>(gen);
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::tuple{(std::has_single_bit(I) ? o : z)...};
      }(std::make_index_sequence<1 << Order>{});
    }

  }

  struct as_var{};
  as_var var;

  //====================================================================================================================
  //! @class hyperdual
  //! @brief hyperdual numbers main abstraction
  //! It is built so that all operations can be done in a streamlined fashion
  //====================================================================================================================
  template<concepts::scalar_base Type, unsigned short Ord>
  requires(Ord >= 1 && Ord <= 4)
  struct hyperdual
  {
    using underlying_type     = Type;
    using is_hyperdual        = void;

    static constexpr unsigned short static_dimension = 1 << Ord;
    static constexpr unsigned short order = Ord;

    /// Default hyperdual constructor
    constexpr hyperdual() noexcept : contents{} {}

    /// Construct a hyperdual condtant from a base value
    template<std::convertible_to<Type> T>
    constexpr hyperdual(T v) noexcept : contents{}
    {

      kumi::get<0>(contents) = v;
    }

    /// Construct a hyperdual variable from a base value
    template<std::convertible_to<Type> T>
    constexpr hyperdual (T v, as_var) noexcept : contents(_::powersof2<order, Type>())
    {
      kumi::get<0>(contents) = v;
    }

    /// Construct a hyperdual instance from a sequences of base values
    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires( (sizeof...(Ts)) >= static_dimension )
      constexpr hyperdual(T0 v0, Ts... vs) noexcept
        : contents{kumi::extract(kumi::tuple{static_cast<Type>(v0), static_cast<Type>(vs)...},
                                 kumi::index<0>, kumi::index<static_dimension>)}
    {}

    template<std::convertible_to<Type> T0, std::convertible_to<Type>... Ts>
    requires( (1+sizeof...(Ts)) == static_dimension )
      constexpr hyperdual(T0 v0, Ts... vs) noexcept : contents{static_cast<Type>(v0), static_cast<Type>(vs)...}
    {}

    /// Construct a hyperdual instance from a properly sized product_type
    constexpr hyperdual(kumi::sized_product_type<static_dimension> auto const& vs) : contents{vs} {}

    /// Constructs a hyperdual instance from an hyperdual of greater order
    template<unsigned short M>
    requires(M >= order)
    constexpr hyperdual(hyperdual<Type,M> const& a) noexcept
    : contents(kumi::extract(a.contents, kumi::index<0>, kumi::index<static_dimension>))
    {}

    /// Assign a greater order hyperdual to another
    template<concepts::hyperdual T>
    constexpr hyperdual& operator=( T const& a) noexcept requires(T::static_dimension > static_dimension)
    {
      return (*this = hyperdual{kumi::extract(a, kumi::index<0>, kumi::index<static_dimension>)});
    }

    //==================================================================================================================
    // ++/--
    //==================================================================================================================

    //! Pre-incrementation operator
    FLX_FORCEINLINE auto& operator++() noexcept { kumi::get<0>(contents)++; return *this; }

    //! Pre-decrementation operator
    FLX_FORCEINLINE auto& operator--() noexcept { kumi::get<0>(contents)--; return *this; }

    //! Post-incrementation operator
    FLX_FORCEINLINE auto operator++(int) noexcept
    {
      auto  that(*this);
      this->operator++();
      return that;
    }

    //! Post-decrementation operator
    FLX_FORCEINLINE auto operator--(int) noexcept
    {
      auto  that(*this);
      this->operator--();
      return that;
    }

    //==================================================================================================================
    //  Tuple-like behavior
    //==================================================================================================================
    using data_type       = kumi::result::fill_t<static_dimension,Type>;
    using is_product_type = void;

    friend constexpr eve::as_logical_t<Type>
    operator==(hyperdual const& a, hyperdual const& b) noexcept
    {
     std::cout << "latte" << std::endl;
     return get<0>(a.contents) == get<0>(b.contents);
    }

    friend constexpr eve::as_logical_t<Type>
    operator!=(hyperdual const& a, hyperdual const& b) noexcept
    {
      return get<0>(a.contents) != get<0>(b.contents);
    }

    data_type contents;
  };

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  template<std::size_t I, typename T, unsigned short N>
  constexpr auto& get(hyperdual<T,N>& c) noexcept { return kumi::get<I>(c.contents); }

  template<std::size_t I, typename T, unsigned short N>
  constexpr auto get(hyperdual<T,N> const& c) noexcept { return kumi::get<I>(c.contents); }

  //====================================================================================================================
  //! @name Deduction Guides
  //! @related hyperdual
  //! @{
  //====================================================================================================================
  /// Deduction guide for constructing from product type
  template<kumi::product_type Tuple>
  hyperdual(Tuple const&) -> hyperdual<kumi::element_t<0,Tuple>, kumi::size_v<Tuple>>;

  /// Deduction guide for constructing from sequence of values
  template<typename T0, std::convertible_to<T0>... Ts>
  hyperdual(T0,Ts... ) -> hyperdual<T0,1+sizeof...(Ts)>;
  //====================================================================================================================
  //! @}
  //====================================================================================================================


  /// create a hyperdual variable from a base value
  template <unsigned short Order, concepts::base T>
  constexpr as_hyperdual_n_t<Order, T> variable(T v) noexcept
  {
    using r_t = as_hyperdual_n_t<Order, T>;
    auto d = _::powersof2<Order, T>();
    kumi::get<0>(d) = v;
    r_t hv(d);
    return hv;
  }
}

namespace flx::_
{
  template<typename T, unsigned short Order>
  inline constexpr unsigned short rank<hyperdual<T,Order>> = 1 << Order;

  template<typename T, unsigned short Order, typename L>
  inline constexpr unsigned short rank<eve::wide<hyperdual<T,Order>,L>> = 1 << Order;
}

#if !defined(flx_DOXYGEN_INVOKED)
// std::tuple adaptation
template<typename T, unsigned short Order>
struct std::tuple_size<flx::hyperdual<T,Order>> : std::integral_constant<std::size_t,1 << Order> {};

template<typename T, unsigned short Order, std::size_t I>
struct std::tuple_element<I, flx::hyperdual<T,Order>>
{
  using type = T;
};

#endif

#include <fluxion/types/io.hpp>
#include <fluxion/types/compounds.hpp>
#include <fluxion/types/operators.hpp>
