//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
// #include <eve/module/polynomial.hpp>
// #include <eve/product_type.hpp>
// #include <flx/forward_automatic/traits.hpp>
// #include <flx/forward_automatic/is_derivable.hpp>
// #include <flx/derivative/derivative.hpp>
// #include <flx/forward_automatic/val.hpp>
// #include <flx/forward_automatic/der.hpp>
// #include <eve/concept/generator.hpp>
// #include <eve/detail/abi.hpp>
// #include <iostream>
// #include <iomanip>
#include <eve/product_type.hpp>
#include <ostream>
#include <flx/forward_automatic/val.hpp>
#include <flx/forward_automatic/der.hpp>
#include <flx/forward_automatic/var.hpp>
#include <flx/forward_automatic/detail/core.hpp>
// #include <flx/forward_automatic/detail/math.hpp>

namespace flx
{
  using eve::like;
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of valder numbers
  //!
  //! **Required header:** `#include <flx.hpp>`
  //!
  //! eve::valder is structure representing pair of function value,  function derivative
  //! and mean to be used in conjunction with eve::wide.
  //!
  //! All eve functions can be called with a valder parameter in place of floating or complex
  //!  parameters with a few restrictions and exceptions
  //!
  //!    - the derivative of piecewise derivable functions (as abs, trunc or frac) are undefined
  //!    - at non derivable points
  //!    - complex non meromorphic functions cannot be derived relative the complex arguments.
  //!    - functions with no sensible derivation properties as predicates or bit-related
  //!      are accepted but always act as if  the derivative was not present and return
  //!      a function value. // TO BE COMPLETED
  //!      They can be used in tests.
  //!    - eve constants of valder<T> are constant of T // TO BE DONE eve constants still not accepted
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<eve::floating_scalar_value Type>
  struct valder : eve::struct_support<valder<Type>, Type, Type>
  {
    using parent = eve::struct_support<valder<Type>, Type, Type>;

    /// Underlying type
    using value_type = Type;

    /// Default constructors
    EVE_FORCEINLINE valder() {}
    EVE_FORCEINLINE valder(Type val) noexcept : parent{val,0} {}
    EVE_FORCEINLINE valder(Type val, Type der)  noexcept : parent{val, der} {}


    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, eve::like<valder> auto const& z)
    {
      return os << std::setprecision(20) << "(" << val(z) << ", "<< der(z) << ")" << std::noshowpos;
    }

    //==============================================================================================
    //  val/der access
    //==============================================================================================
    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(tag::val_, like<valder> auto&& z)
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(tag::der_, like<valder> auto && z)
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    //  functions support
    //==============================================================================================
    template<typename Tag, typename Z1>
    requires(eve::like<Z1,valder>)
      EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                    , Z1 const& z1
                                                    ) noexcept
    ->    decltype(detail::valder_unary_dispatch(tag, z1))
    {
      return detail::valder_unary_dispatch(tag, z1);
    }

    template<typename Tag, typename Z1, typename Z2>
    requires(eve::like<Z1,valder> || eve::like<Z2,valder>)
      EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                    , Z1 const& z1, Z2 const& z2
                                                    ) noexcept
    ->    decltype(detail::valder_binary_dispatch(tag, z1, z2))
    {
      return detail::valder_binary_dispatch(tag, z1, z2);
    }


//     template<typename Tag, typename Z1,  typename ...Zs>
//     requires(like<Z1,valder> || (... || like<Zs,valder>))
//       EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
//                                                     , Z1 const& z1, Zs const&... zs
//                                                     ) noexcept
//     ->    decltype(detail::valder_nary_dispatch(tag, z1, zs...))
//     {
//       return detail::valder_nary_dispatch(tag, z1, zs...);
//     }

    //==============================================================================================
    // helpers
    //==============================================================================================
    // mask helper
    //==============================================================================================
//     template<eve::conditional_expr Cond>
//     static EVE_FORCEINLINE auto if_else_1(Cond const & cond)
//     {
//       if constexpr(Cond::has_alternative) return cond.rebase(1);
//       else return cond.else_(1);
//     }
//     template<eve::conditional_expr Cond>
//     static EVE_FORCEINLINE auto if_else_0(Cond const & cond)
//     {
//       if constexpr(Cond::has_alternative) return cond.rebase(0);
//       else return cond.else_(0);
//     }

    //==============================================================================================
    // functions which do not have in fluxion an implemented derivative decorated version
    //==============================================================================================
//     template<typename Func, typename Z1, typename... Zs>
//     static EVE_FORCEINLINE auto compute(Func f, Z1 const& z1, Zs const& ... zs)
//     {
//       if constexpr(eve::decorator<Z1>)
//         return compute(z1(f), val(zs)...);
//       else if constexpr(eve::conditional_expr<Z1>)
//         return compute(f[z1], val(zs)...);
//       else
//         return f(val(z1), val(zs)...);
//     }

    //==============================================================================================
    //  nary  functions support
    //==============================================================================================
//     template<typename Tag, typename Z1,  typename ...Zs>
//     requires(like<Z1,valder> || (... || like<Zs,valder>))
//     EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
//                                                   , Z1 const& z1, Zs const&... zs
//                                                   ) noexcept
//                             ->    decltype(detail::valder_nary_dispatch(tag, z1, zs...))
//     {
//       return detail::valder_nary_dispatch(tag, z1, zs...);
//     }


    //==============================================================================================
    // Constants support
    //==============================================================================================
    template<typename Tag, eve::like<valder> VD>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag, eve::as<VD> const&) noexcept
    {
      eve::detail::callable_object<Tag> cst;
      if constexpr(std::same_as<Tag, eve::tag::true__> || std::same_as<Tag, eve::tag::false__>)
        return cst(as(real(VD{})));
      else
        return VD{ cst(eve::as<Type>{}), Type{0}};
    }

    //==============================================================================================
    //  Operators
    //==============================================================================================
    //==============================================================================================
    // +
    //==============================================================================================
    EVE_FORCEINLINE friend auto operator+(like<valder> auto const& z) noexcept { return z; }

    EVE_FORCEINLINE friend auto& operator+= ( eve::like<valder> auto & self
                                            , eve::like<valder> auto const & o
                                            ) noexcept
    {
      using v_t = decltype(eve::add(val(self), val(o)));
      using r_t = flx::as_valder_t<v_t>;
      auto [vs, ds] = self;
      auto [v, d] = o;
      return self = r_t{vs+v, ds+d};
    }

    template < typename Z>
    EVE_FORCEINLINE friend auto& operator+= ( eve::like<valder> auto& self
                                            , Z const& o
                                            ) noexcept
        requires(like<Z,Type> || std::convertible_to<Z,Type>)
    {
      using v_t = decltype(eve::add(val(self), val(o)));
      using r_t = flx::as_valder_t<v_t>;
      auto [vs, ds] = self;
      return self = r_t{vs+o, ds};
    }

//     template < typename Z1, typename Z2>
//     requires(like<Z1,valder> || like<Z2,valder>)
//     EVE_FORCEINLINE friend auto operator+(  Z1 const & z1, Z2 const & z2
//                                           ) noexcept
//     {
//       std::cout << "+++0" << std::endl;
//       return eve::add(z1, z2);
//     }

//     EVE_FORCEINLINE friend auto operator+(  eve::like<valder> auto const & z1
//                                          ,  eve::like<valder> auto const & z2
//                                           ) noexcept
//     {
//       std::cout << "+++1" << std::endl;
//       return eve::add(z1, z2);
//     }

//     //==============================================================================================
//     // -
//     //==============================================================================================
//     template< like<valder> Z>
//     EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
//     {
//       return Z{-val(z), -der(z)};
//     }

//     template<like<valder> Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto& operator-= ( eve::like<valder> auto & self
//                                             , eve::like<valder> auto const & o
//                                             ) noexcept
//     {
//       val(self) -= val(o);
//       der(self) -= der(o);
//       return self;
//     }

//     template < typename Z>
//     EVE_FORCEINLINE friend auto& operator-= ( eve::like<valder> auto& self
//                                             , Z const& o
//                                             ) noexcept
//     {
//       val(self) -= val(o);
//       return self;
//     }

//     template < typename Z1, typename Z2>
//     EVE_FORCEINLINE friend auto operator-(  const Z1 &z1
//                                           , const Z2 &z2
//                                           ) noexcept
//     requires (eve::like<Z1, valder> || eve::like<Z2, valder>)
//     {
//       return eve::sub(z1, z2);
//     }

//     //==============================================================================================
//     // *
//     //==============================================================================================
//     template<like<valder> Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto& operator*= (Z1& self, Z2 const& o) noexcept
//     {
//       auto [a, b] = self;
//       auto [c, d] = o;
//       der(self) = eve::sum_of_prod(a, d, b, c);
//       val(self) = val(self)*c;
//       return self;
//     }

//     template<typename Z>
//     EVE_FORCEINLINE friend auto& operator*=(like<valder> auto& self, Z const & o) noexcept
//     requires(like<Z,Type> || std::convertible_to<Z,Type>)
//     {
//       val(self) *= o;
//       der(self) *= o;
//       return self;
//     }

//     template < typename Z1, typename Z2>
//     EVE_FORCEINLINE friend auto operator*(  const Z1 & z1
//                                           , const Z2 & z2
//                                           ) noexcept
//     requires (eve::like<Z1, valder> || eve::like<Z2, valder>)
//     {
//       return eve::mul(z1, z2);
//     }

//     //==============================================================================================
//     // /
//     //==============================================================================================
//     template<like<valder> Z1, like<valder> Z2>
//     EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
//     {
//       auto [a, b] = self;
//       auto [c, d] = o;
//       auto invo2 = eve::rec(eve::sqr(val(o)));
//       val(self) /= c;
//       der(self) = diff_of_prod(c, b, a, d)/invo2;
//       return self;
//     }

//     template<typename Z>
//     EVE_FORCEINLINE friend auto& operator/=(like<valder> auto& self, Z const & o) noexcept
//     requires(like<Z,Type> || std::convertible_to<Z,Type>)
//     {
//       auto invo2 = eve::rec(eve::sqr(val(o)));
//       val(self) /= o;
//       der(self) /= o;
//       return self;
//     }

//     template < typename Z1, typename Z2>
//     EVE_FORCEINLINE friend auto operator/(  const Z1 & z1
//                                           , const Z2 & z2
//                                           ) noexcept
//     requires (eve::like<Z1, valder> && eve::like<Z2, valder>)
//     {
//       return eve::div(z1, z2);
//     }


//     template<typename Func, eve::like<valder> Z>
//     static EVE_FORCEINLINE auto deriv(Func f, Z const & z)
//     {
//       auto [v, d] = z;
//       return Z{f(v), flx::derivative(f)(v)*d};
//     }

//     template<typename Func, eve::decorator D, eve::like<valder> Z>
//     static EVE_FORCEINLINE auto deriv(Func f, D const &, Z const & z)
//     {
//       auto [v, d] = z;
//       return Z{D()(f)(v), flx::derivative(f)(v)*d};
//     }

//     template<typename Func, eve::conditional_expr C, eve::like<valder> Z>
//     static EVE_FORCEINLINE auto deriv(Func f, C const & cond, Z const & z)
//     {
//       auto [v, d] = z;
//       return Z{f[cond](v), flx::derivative(f[if_else_1(cond)])(v)*d};
//     }

//     template<typename Func, eve::conditional_expr C, eve::decorator D, eve::like<valder> Z>
//     static EVE_FORCEINLINE auto deriv(Func f, C const & cond, D const &, Z const & z)
//     {
//       auto [v, d] = z;
//       return Z{D()(f[cond])(v), flx::derivative(D()(f[if_else_1(cond)]))(v)*d};
//     }

//     //==============================================================================================
//     //  n_ary functions
//     //==============================================================================================
//     template<typename Func, eve::decorator D, typename V0, typename V1, typename... Vs>
//     static EVE_FORCEINLINE auto deriv(Func f, D const &, V0 const& z0, V1 const& z1, Vs const&... zs )
//     {
//       return deriv(D()(f), z0, z1, zs...);
//     }

//     template<typename Func, eve::conditional_expr C, typename V0, typename V1, typename... Vs>
//     static EVE_FORCEINLINE auto deriv(Func f, C const & c, V0 const& z0, V1 const& z1, Vs const&... zs )
//     {
//       return deriv(f[c], z0, z1, zs...);
//     }

//     template<typename Func, typename V0, typename V1, typename... Vs>
//     static EVE_FORCEINLINE auto deriv(Func f, V0 const& z0, V1 const& z1 , Vs const&... zs)
//       requires(!eve::conditional_expr<V0> && !eve::decorator<V0>)
//     {
//       using v_t = decltype(f(val(z0),val(z1),val(zs)...));
//       using r_t = flx::as_valder_t<v_t>;

//       auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
//       auto tzs = kumi::make_tuple(zs...);

//       auto snd0 = [&](auto z0){
//         if constexpr(!eve::like<decltype(z0), valder>) return eve::zero(eve::as(val(z0)));
//         else return kumi::apply(derivative_1st(f),vs);
//       };
//       auto snd1 = [&](auto z1){
//         if constexpr(!eve::like<decltype(z1), valder>) return eve::zero(eve::as(val(z1)));
//         else return kumi::apply(derivative_2nd(f),vs);
//       };

//       v_t d = eve::sum_of_prod ( v_t(snd0(z0)), v_t(der(z0)), v_t(snd1(z1)), v_t(der(z1))   );

//       if constexpr(sizeof...(zs)!= 0)
//       {
//         [&]<std::size_t... I>(std::index_sequence<I...>)
//         {
//           auto ifam = [](auto a,  auto b, auto c){
//             if constexpr(eve::floating_value<decltype(c)>) return a;
//             else return eve::fam(a, b, v_t(der(c)));
//           };
//           ((d = ifam(d, kumi::apply(derivative_nth<I+3>(f),vs), get<I>(tzs))),...);
//         }(std::index_sequence_for<Vs...>{});
//       }
//       return r_t{ kumi::apply(f,vs), d};
//     }

//     //==============================================================================================
//     // Functions support
//     //==============================================================================================
//     //==============================================================================================
//     // unary functions
//     template<typename Tag>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag
//                                                , eve::like<valder> auto const& v) noexcept
//     requires( has_derivation_v<Tag> )
//     {
//       if constexpr(is_derivable_v<Tag>) return deriv( eve::detail::callable_object<Tag>{}, v);
//       else                              return compute( eve::detail::callable_object<Tag>{}, v);
//    }

//     template<typename Tag, eve::conditional_expr C>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag
//                                                , C const & c
//                                                , eve::like<valder> auto const& v) noexcept
//     requires( has_derivation_v<Tag> )
//     {
//       if constexpr(is_derivable_v<Tag>)
//         return eve::detail::mask_op(c, eve::detail::callable_object<Tag>{}, v);
//       else
//         return compute( eve::detail::callable_object<Tag>{}, c, v);
//     }

//     template<typename Tag, eve::decorator D>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag
//                                                , D const & d
//                                                , eve::like<valder> auto const& v) noexcept
//     requires( has_derivation_v<Tag> )
//     {
//       if constexpr(is_derivable_v<Tag>) return deriv( eve::detail::callable_object<Tag>{}, d, v);
//       else                              return compute( eve::detail::callable_object<Tag>{}, d, v);
//     }

//     //==============================================================================================
//     // n-ary functions
//     template<typename Tag, typename V0, typename ... Vs>
//     EVE_FORCEINLINE friend auto tagged_dispatch (Tag, V0 const& v0, Vs const&... vs ) noexcept
//     requires( has_derivation_v<Tag> && (eve::like < V0, valder > || (eve::like < Vs, valder > ||...)))
//     {
//       if constexpr(is_derivable_v<Tag>)
//       {
//         return deriv( eve::detail::callable_object<Tag>{}, v0, vs ...);
//       }
//       else
//       {
//         return compute( eve::detail::callable_object<Tag>{}, v0, vs ...);
//       }
//     }

//     template<typename Tag, eve::conditional_expr C, typename V0, typename ... Vs>
//     EVE_FORCEINLINE friend auto tagged_dispatch (Tag const &, C const& c, V0 const& v0, Vs const&... vs ) noexcept
//     requires( has_derivation_v<Tag> && (eve::like < V0, valder > || (eve::like < Vs, valder > ||...)))
//     {
//       if constexpr(is_derivable_v<Tag>)
//       {
//         auto deri = [&](auto p0, auto ...ps)
//         {
//           eve::detail::callable_object<Tag> co{};
//           return deriv(co, p0, ps ...);
//         }
// ;
//         return eve::detail::mask_op(c, deri, v0, vs ...);
//       }
//       else
//       {
//         auto compu = [&](auto p0, auto ...ps)
//         {
//           eve::detail::callable_object<Tag> co{};
//           return compute(co, p0, ps ...);
//         };

//         return eve::detail::mask_op(c, compu, v0, vs ...);
//       }
//     }

//     //==============================================================================================/////////////////////////
//     //==  peculiar cases
//     //==============================================================================================/////////////////////////
//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exponent_, Z const& z) noexcept
//     {
//       return eve::exponent(val(z));
//     }

//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mantissa_, Z const& z) noexcept
//     {
//       return Z{eve::mantissa(val(z)), der(z)};
//     }

//     template<eve::like<valder> Z, eve::value N>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ldexp_
//                                                 , Z const& z,  N const& n) noexcept
//     {
//       auto nn = eve::convert(n, eve::as<eve::element_type_t<decltype(val(z))>>());
//       return Z{eve::ldexp(val(z), nn), eve::ldexp(eve::one(eve::as(val(z))), nn)*der(z)};
//     }

//     //==============================================================================================
//     //  Binary functions
//     //==============================================================================================
//     template < typename Z1,  typename Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
//                                                 , Z1 const & z1
//                                                 , Z2 const & z2
//                                                 ) noexcept
//     requires ( eve::like<Z1, valder> || eve::like<Z2, valder> )
//     {
//       return eve::max( eve::ulpdist(val(z1), val(z2))
//                      , eve::ulpdist(der(z1), der(z2)));
//     }

//     //==============================================================================================
//     //  returning tuples
//     //==============================================================================================
//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sincos_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto [s, c]= eve::sincos(v);
//       return kumi::tuple{Z{s, d*c}, Z{c, -d*s}};
//     }

//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpicospi_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto [s, c]= eve::sinpicospi(v);
//       auto fac = eve::pi(eve::as(v));
//       return kumi::tuple{Z{s, d*c*fac}, Z{c, -d*s*fac}};
//     }

//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sindcosd_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto [s, c]= eve::sindcosd(v);
//       auto fac = eve::deginrad(d);
//       return kumi::tuple{Z{s, c*fac}, Z{c, -s*fac}};
//     }

//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinhcosh_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto [s, c]= eve::sinhcosh(v);
//       return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
//     }

//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::lambert_
//                                                , Z const& z ) noexcept
//     {
//       auto [v, d] = z;
//       auto [s, c]= eve::lambert(v);
//     auto [ds, dc]= flx::derivative(eve::lambert)(v);
//       return kumi::tuple{Z{s, d*ds}, Z{c, d*dc}};
//     }

//     //// if_else
//     template<typename Z1,  typename Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::if_else_
//                                                 , auto const & vc
//                                                 , Z1 const & a
//                                                 , Z2 const & b
//                                                 ) noexcept
//     requires ( eve::like<Z1, valder> || eve::like<Z2, valder> )
//     {
//       auto va = val(a); auto da = der(a);
//       auto vb = val(b); auto db = der(b);
//       using v_t = decltype(eve::if_else(vc, va, vb));
//       using r_t = as_valder_t<v_t>;
//       return r_t{eve::if_else(vc, va, vb), eve::if_else(vc, da, db)};
//     }

//     template < eve::like < valder> Z2, eve::generator < typename Z2::value_type> Constant>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
//                                                , auto const & vc
//                                                , Constant const& a
//                                                , Z2 const& b ) noexcept
//     {
//       auto vb = val(b); auto db = der(b);
//       using v_t = decltype(eve::if_else(vc, a, vb));
//       using r_t = as_valder_t<v_t>;
//       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
//     }

//     template < eve::like < valder> Z1, eve::generator < typename Z1::value_type> Constant>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
//                                                , auto const & vc
//                                                , Z1 const& b
//                                                , Constant const& a

//                                                ) noexcept
//     {
//       auto vb = val(b); auto db = der(b);
//       using v_t = decltype(eve::if_else(vc, a, vb));
//       using r_t = as_valder_t<v_t>;
//       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
//     }

//     //// ifnot_else
//     template< typename Z1,  typename Z2>
//     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ifnot_else_
//                                                 , auto const & c
//                                                 , Z1 const & a
//                                                 , Z2 const & b
//                                                 ) noexcept
//     requires ( eve::like<Z1, valder> || eve::like<Z2, valder> )
//     {
//       return eve::if_else(c, b, a);
//     }

//     //// modf
//     template<eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::modf_
//                                                , Z const& z ) noexcept
//     {
//       return kumi::tuple{eve::modf(val(z)), Z{{zero(as(val(z))),zero(as(val(z)))}}};
//     }

//     //// tchebytchev
//     template<typename N, eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tchebytchev_
//                                                , N const& n
//                                                , Z const& z ) noexcept
//     {
//       using v_t = decltype(eve::tchebytchev(n, val(z)));
//       using r_t = as_valder_t<v_t>;
//       return r_t{eve::tchebytchev(n, val(z)), flx::derivative_2nd(eve::tchebytchev)(n, val(z))*der(z)};
//     }

//     template<typename N, eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tchebytchev_
//                                                , eve::kind_1_type const &
//                                                , N const& n
//                                                , Z const& z ) noexcept
//     {
//       return tchebytchev(n, z);
//     }
//     template<typename N, eve::like<valder> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tchebytchev_
//                                                , eve::kind_2_type const &
//                                                , N const& n
//                                                , Z const& z ) noexcept
//     {
//       using v_t = decltype(eve::tchebytchev(n, val(z)));
//       using r_t = as_valder_t<v_t>;
//       return r_t{eve::kind_2_type()(eve::tchebytchev)(n, val(z))
//           , eve::tchebytchev(eve::decorated<flx::derivative_<2>(eve::kind_2_type)>(), n, val(z))*der(z)};
//     }
  };
}
