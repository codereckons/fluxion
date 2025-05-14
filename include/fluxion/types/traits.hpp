//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/as.hpp>
#include <bit>

namespace flx
{
  template<concepts::scalar_base, unsigned short Ord>
  requires(Ord >= 1 && Ord <= 4)
  struct hyperdual;
}

namespace flx::_
{
  // Force a type to be looked at as a wide so we can apply wide-like type preserving semantic in type computations
  template<typename T> struct  sema                             { using type = T; };
  template<typename T> struct  sema<eve::logical<T>>  : sema<T> {};
  template<typename T, typename N>
  struct  sema<eve::wide<T,N>>                                  { using type = eve::wide<eve::underlying_type_t<T>>; };
  template<concepts::hyperdual T>
  struct  sema<T>                                               { using type = eve::wide<eve::underlying_type_t<T>>; };

  template<typename T>                  using   sema_t  = typename sema<T>::type;

  // Convert a Base type to a potential wide if any appear in T...
  template<typename Base, typename... T>
  using widen = std::conditional_t< std::max({eve::cardinal_v<T>...}) != 1ULL
                                  , eve::as_wide_t<Base,eve::fixed<std::max({eve::cardinal_v<T>...})>>
                                  , eve::element_type_t<Base>
                                  >;
}

namespace flx
{
  //====================================================================================================================
  //! @addtogroup traits
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //! @brief Obtains the number of dimensions of the algebra containing a given type
  //!
  //!
  //! If `T` models a value of \f$\mathbb{R}\f$, evaluates to 1.
  //!
  //! @tparam T Type to analyze.
  //====================================================================================================================

constexpr unsigned short max_dimension_v = 16;
constexpr unsigned short max_order = 4;

#if !defined(flx_DOXYGEN_INVOKED)
  template<typename T>  inline constexpr unsigned short dimension_v = max_dimension_v;
  template<typename T>  inline constexpr unsigned short order_v    =  max_order;
#else
  template<typename T>  inline constexpr unsigned short dimension_v = *implementation-defined*;
  template<typename T>  inline constexpr unsigned short order_v    =  *implementation-defined*;
#endif


  template<concepts::hyperdual T> inline constexpr auto dimension_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::static_dimension;
  template<concepts::hyperdual T> inline constexpr auto order_v<T> = eve::element_type_t<std::remove_cvref_t<T>>::order;

  template<typename T>                    struct as_base_type                     { using type = T; };
  template<typename T,unsigned short Dim> struct as_base_type<hyperdual<T,Dim>>   { using type = T; };
  template<typename T,typename N>         struct as_base_type<eve::wide<T,N>>
  {
    using type = eve::wide<typename as_base_type<T>::type,N>;
  };

  //====================================================================================================================
  //! @brief Compute the base type associated to a Hyperdual-like type
  //!
  //! @tparam T Type to convert to a base type.
  //====================================================================================================================
  template<typename T>
  using as_base_type_t = typename as_base_type<T>::type;

  template<unsigned short Ord, typename... Ts>
  struct  as_hyperdual_n;

  template<unsigned short Ord, typename... Ts>
  requires( Ord > 0 && requires(Ts... ts) { eve::add( std::declval<_::sema_t<Ts>>()...); } )
  struct  as_hyperdual_n<Ord,Ts...>
#if !defined(flx_DOXYGEN_INVOKED)
        : as_hyperdual_n<Ord, _::widen<decltype(eve::add( std::declval<_::sema_t<Ts>>()...)),Ts...>>
#endif
  {};

#if !defined(flx_DOXYGEN_INVOKED)
  template<unsigned short Ord, typename... Ts>
  requires( Ord > 0 && !requires(Ts... ts) { eve::add( std::declval<_::sema_t<Ts>>()...); } )
  struct  as_hyperdual_n<Ord, Ts...> {};

  template<unsigned short Ord, typename T>
  requires(Ord > 0)
  struct as_hyperdual_n<Ord, T>
  {
    static constexpr auto card = eve::cardinal_v<T>;
    using cd_t  = hyperdual<eve::as_floating_point_t<eve::underlying_type_t<T>>,
                            Ord>;
    using type  = std::conditional_t<card != 1ULL, eve::wide<cd_t,eve::fixed<card>>, cd_t>;
  };
#endif

  //====================================================================================================================
  //! @brief Computes a Hyperdual type of a given dimension
  //!
  //! @tparam Ord order of the Hyperdual algebra to use.
  //! @tparam Ts  Types used to compute the Hyperdual underlying type.
  //====================================================================================================================
  template<unsigned short Ord, typename... Ts>
  using as_hyperdual_n_t = typename as_hyperdual_n<Ord,Ts...>::type;

  template<typename... Ts>
  requires( requires(Ts... ts) { typename as_hyperdual_n<std::min( {order_v<Ts>...} ), Ts...>::type; } )
  struct as_hyperdual : as_hyperdual_n<std::min( {order_v<Ts>...} ), Ts...>
  {};
}

namespace flx
{
  namespace _
  {
    template<typename T>
    using common_base = eve::as_floating_point_t<as_base_type_t<T>>;
  }

  //====================================================================================================================
  //! @brief Computes the best fitting Hyperdual type from a series of types.
  //!
  //! @tparam Ts  Types used to compute the Hyperdual underlying type.
  //====================================================================================================================
  template<typename... Ts>
  using as_hyperdual_t = typename as_hyperdual<Ts...>::type;

  template<auto Callable, typename... Ts>
  using expected_result_t = as_hyperdual_n_t < std::min( {dimension_v<Ts>...} )
                                                  , decltype( Callable( std::declval<as_base_type_t<Ts>>()...) )
                                                  >;

  using eve::as;

  //====================================================================================================================
  //! @struct as_base
  //! @brief Lightweight type-wrapper of base value type
  //!
  //! Wraps the base type associated to `T` into a constexpr, trivially constructible empty class to optimize passing
  //! type parameters via object instead of via template parameters.
  //!
  //! @tparam T Type to wrap
  //====================================================================================================================
  template<typename T>
  struct as_base : as<as_base_type_t<T>>
  {
    constexpr           as_base()          noexcept {}
    explicit constexpr  as_base(T const&)  noexcept {}
  };
  //====================================================================================================================
  //!  @}
  //====================================================================================================================


//   //====================================================================================================================
//   //! @struct complexify
//   //! @brief compute the cayley dickson type associated to a floating type or any other type.
//   //!
//   //! if the type is an eve::floating_value return the complex type associated else let the type as is.
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

  template<typename... Ts>       struct as_hyperdual_like        : as_hyperdual<Ts...> {};
  template<concepts::base... Ts> struct as_hyperdual_like<Ts...> : eve::common_value<Ts...> {};
  template<typename... Ts> using as_hyperdual_like_t = typename as_hyperdual_like<Ts...>::type;

}
