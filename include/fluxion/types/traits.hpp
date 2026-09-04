//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/same_lanes.hpp>
#include <fluxion/types/concepts.hpp>
#include <fluxion/types/helpers.hpp>
#include <bit>

namespace flx
{
  template<concepts::scalar_base, unsigned int Ord>
    requires(Ord >= 1 && Ord <= 4)
  struct hyperdual;
}

namespace flx::_
{
  // The arithmetic semantics of a type: the scalar its components are made of, whatever wraps them.
  // Lanes are none of its business, widen puts them back below from the cardinal each type really
  // has. Reading them here through a wide of the element's native cardinal, as this used to,
  // invents a lane count that then acts as a constraint, and refuses a pack whose real lanes agree.
  template<typename T> using sema_t = eve::underlying_type_t<T>;

  // What the arguments that hold a structure, a hyperdual or a wide, agree their components are
  // made of, void when the pack holds only lone scalars. Two that disagree have no common element:
  // EVE promotes nothing between element types, at any width, and a wide converts to nothing.
  template<typename A, typename B> struct agree
  {
  };
  template<typename A> struct agree<A, void>
  {
    using type = A;
  };
  template<typename B> struct agree<void, B>
  {
    using type = B;
  };
  template<> struct agree<void, void>
  {
    using type = void;
  };
  template<typename A> struct agree<A, A>
  {
    using type = A;
  };

  // A lone scalar base value speaks for nobody: it converts into whatever it is mixed with, the way
  // a scalar converts into a wide under EVE. Everything else states an element and has to be agreed
  // with, a wide of floats being no more convertible to an algebra of doubles than to a wide of
  // them.
  template<typename T>
  inline constexpr bool adapts = !concepts::hyperdual<T> && eve::cardinal_v<T> == 1;

  template<typename... Ts> struct declared_element
  {
    using type = void;
  };
  template<typename T, typename... Ts>
  struct declared_element<T, Ts...>
      : agree<std::conditional_t<adapts<T>, void, sema_t<T>>,
              typename declared_element<Ts...>::type>
  {
  };

  template<typename... Ts> using declared_element_t = typename declared_element<Ts...>::type;

  // Where every argument adapts, nothing has been stated and EVE decides among the scalars alone,
  // which is why the two cases cannot share one expression.
  template<typename Element, typename... Ts> struct pack_element
  {
    using type = Element;
  };
  template<typename... Ts> struct pack_element<void, Ts...>
  {
  };
  template<typename... Ts>
    requires requires { eve::add(std::declval<Ts>()...); }
  struct pack_element<void, Ts...>
  {
    using type = sema_t<decltype(eve::add(std::declval<Ts>()...))>;
  };

  template<typename... Ts>
  using pack_element_t = typename pack_element<declared_element_t<Ts...>, Ts...>::type;

  // Mixable when that element type exists, and when the arguments that really are wide agree on how
  // many lanes they carry. The second half is what sema_t no longer says.
  template<typename... Ts>
  concept mixable = eve::same_lanes_or_scalar<Ts...> &&
                    requires { typename pack_element<declared_element_t<Ts...>, Ts...>::type; };

  // Convert a Base type to a potential wide if any appear in T...
  template<typename Base, typename... T>
  using widen =
      std::conditional_t<std::max({eve::cardinal_v<T>...}) != 1ULL,
                         eve::as_wide_t<Base, eve::fixed<std::max({eve::cardinal_v<T>...})>>,
                         eve::element_type_t<Base>>;
}

namespace flx
{
  //====================================================================================================================
  //! @addtogroup traits
  //! @{
  //====================================================================================================================
  /// Widest algebra the library builds, sixteen components
  constexpr unsigned int max_dimension_v = 16;
  /// Highest derivative order the library carries
  constexpr unsigned int max_order       = 4;

  //=====================================================================================================
  //! @brief Obtains the number of dimensions of the algebra containing a given type
  //!
  //! If `T` models a value of \f$\mathbb{R}\f$, evaluates to max_dimension_v: a base value
  //! never narrows what it meets.
  //!
  //! @tparam T Type to analyze.
  //=====================================================================================================
#if !defined(flx_DOXYGEN_INVOKED)
  template<typename T> inline constexpr unsigned int dimension_v = max_dimension_v;
#else
  template<typename T> inline constexpr unsigned int dimension_v = *implementation - defined*;
#endif

  //=====================================================================================================
  //! @brief Obtains the order of derivation obtained in the algebra containing a given type
  //!
  //! If `T` models a value of \f$\mathbb{R}\f$, evaluates to max_order: a base value loses
  //! nothing at any order, and the min over a mixed pack then ignores it.
  //!
  //! @tparam T Type to analyze.
  //=====================================================================================================
#if !defined(flx_DOXYGEN_INVOKED)
  template<typename T> inline constexpr unsigned int order_v = max_order;
#else
  template<typename T> inline constexpr unsigned int order_v = *implementation - defined*;
#endif

  // The parameters belong to the primary above; -Wdocumentation refuses a @tparam on a
  // specialization.
  template<concepts::hyperdual T>
  inline constexpr auto dimension_v<T> =
      eve::element_type_t<std::remove_cvref_t<T>>::static_dimension;

  template<concepts::hyperdual T>
  inline constexpr auto order_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::order;

  template<typename T> struct as_base_type
  {
    using type = T;
  };
  template<typename T, unsigned int Dim> struct as_base_type<hyperdual<T, Dim>>
  {
    using type = T;
  };
  template<typename T, typename N> struct as_base_type<eve::wide<T, N>>
  {
    using type = eve::wide<typename as_base_type<T>::type, N>;
  };

  //====================================================================================================================
  //! @brief Compute the base type associated to a Hyperdual-like type
  //!
  //! @tparam T Type to convert to a base type.
  //====================================================================================================================
  template<typename T> using as_base_type_t = typename as_base_type<T>::type;

  template<unsigned int Ord, typename... Ts> struct as_hyperdual_n;

  template<unsigned int Ord, typename... Ts>
    requires(Ord > 0 && _::mixable<Ts...>)
  struct as_hyperdual_n<Ord, Ts...>
#if !defined(flx_DOXYGEN_INVOKED)
      : as_hyperdual_n<Ord, _::widen<_::pack_element_t<Ts...>, Ts...>>
#endif
  {
  };

#if !defined(flx_DOXYGEN_INVOKED)
  template<unsigned int Ord, typename... Ts>
    requires(Ord > 0 && !_::mixable<Ts...>)
  struct as_hyperdual_n<Ord, Ts...>
  {
  };

  template<unsigned int Ord, typename T>
    requires(Ord > 0)
  struct as_hyperdual_n<Ord, T>
  {
    static constexpr auto card = eve::cardinal_v<T>;
    using cd_t = hyperdual<eve::as_floating_point_t<eve::underlying_type_t<T>>, Ord>;
    using type = std::conditional_t<card != 1ULL, eve::wide<cd_t, eve::fixed<card>>, cd_t>;
  };
#endif

  //====================================================================================================================
  //! @brief Computes a Hyperdual type of a given dimension
  //!
  //! @tparam Ord order of the Hyperdual algebra to use.
  //! @tparam Ts  Types used to compute the Hyperdual underlying type.
  //====================================================================================================================
  template<unsigned int Ord, typename... Ts>
  using as_hyperdual_n_t = typename as_hyperdual_n<Ord, Ts...>::type;

  template<typename... Ts>
    requires(
        requires(Ts... ts) { typename as_hyperdual_n<std::min({order_v<Ts>...}), Ts...>::type; })
  struct as_hyperdual : as_hyperdual_n<std::min({order_v<Ts>...}), Ts...>
  {
  };
}

namespace flx
{
  namespace _
  {
    template<typename T> using common_base = eve::as_floating_point_t<as_base_type_t<T>>;
  }

  //====================================================================================================================
  //! @brief Computes the best fitting Hyperdual type from a series of types.
  //!
  //! @tparam Ts  Types used to compute the Hyperdual underlying type.
  //====================================================================================================================
  template<typename... Ts> using as_hyperdual_t = typename as_hyperdual<Ts...>::type;

  template<auto Callable, typename... Ts>
  using expected_result_t =
      as_hyperdual_n_t<std::min({order_v<Ts>...}),
                       decltype(Callable(std::declval<as_base_type_t<Ts>>()...))>;

  using eve::as;

  //====================================================================================================================
  //! @brief Lightweight type-wrapper of base value type
  //!
  //! Wraps the base type associated to `T` into a constexpr, trivially constructible empty class to
  //! optimize passing type parameters via object instead of via template parameters.
  //!
  //! @tparam T Type to wrap
  //====================================================================================================================
  template<typename T> struct as_base : as<as_base_type_t<T>>
  {
    constexpr as_base() noexcept {}
    explicit constexpr as_base(T const&) noexcept {}
  };
  //====================================================================================================================
  //!  @}
  //====================================================================================================================

  //   //====================================================================================================================
  //   //! @struct complexify
  //   //! @brief compute the hyperdual type associated to a floating type or any other type.
  //   //!
  //   //! if the type is an eve::floating_value return the complex type associated else let the
  //   type as is.
  //   //!
  //   //! @tparam T Type to wrap
  //   //====================================================================================================================
  //   template<typename T> struct complexify
  //   {
  //     using type = T;
  //   };

  //   template<eve::floating_value T> struct complexify<T>
  //   {
  //     using type = flx::as_hyperdual_n_t<2, T>;
  //   };

  //   template < typename T> using complexify_t =  typename complexify<T>::type;

  //====================================================================================================================
  //! @brief Compute the hyperdual_like type associated to a Hyperdual-like family of types
  //!
  //! @tparam Ts Types used to compute the Hyperdual_like common type.
  //====================================================================================================================
  template<typename... Ts> struct as_hyperdual_like : as_hyperdual<Ts...>
  {
  };

  template<typename T, typename Ts>
  struct as_hyperdual_like<T, coefficients<Ts>>
      : as_hyperdual_like<T, kumi::apply_traits_t<as_hyperdual_like, Ts>>
  {
  };

  template<typename T, typename Ts>
  struct as_hyperdual_like<T, nodes<Ts>>
      : as_hyperdual_like<T, kumi::apply_traits_t<as_hyperdual_like, Ts>>
  {
  };

  template<concepts::base... Ts> struct as_hyperdual_like<Ts...> : eve::common_value<Ts...>
  {
  };
  template<typename... Ts> using as_hyperdual_like_t = typename as_hyperdual_like<Ts...>::type;
}
