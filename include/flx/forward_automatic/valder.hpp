//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/product_type.hpp>
#include <flx/forward_automatic/traits.hpp>
#include <flx/forward_automatic/is_derivable.hpp>
#include <flx/derivative/derivative.hpp>
#include <eve/concept/generator.hpp>
#include <eve/detail/abi.hpp>
#include <iostream>
#include <iomanip>

namespace flx
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of valder numbers
  //!
  //! **Required header:** `#include <eve/module/ad.hpp>`
  //!
  //! eve::valder is structure representing pair of function value,  function derivative
  //! and mean to be used in conjunction with eve::wide.
  //!
  //! All eve functions can be called with a valder parameter in place of floating or complex parameters
  //! with a few restrictions and exceptions
  //!
  //!    - the derivative of piecewise derivable functions (as abs, trunc or frac) are undefined at non derivable points
  //!    - complex non meromorphic functions cannot be derived relative the complex arguments.  // TO BE DONE complex still not accepted
  //!    - functions with no sensible derivation properties as predicates or bit-related
  //!      are accepted but always act as if  the derivative was not present and return a function value. // TO BE COMPLETED
  //!      They can be used in tests.
  //!    - eve constants of valder<T> are constant of T // TO BE DONE eve constants still not accepted
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<eve::floating_scalar_value Type>
  struct valder : eve::struct_support<valder<Type>, Type, Type>
  {
    //   using eve_disable_ordering = void;
    using parent = eve::struct_support<valder<Type>, Type, Type>;

    /// Underlying type
    using value_type = Type;

    /// Default constructor
    EVE_FORCEINLINE valder(Type val = 0, Type der = 0)  noexcept : parent{val, der} {}


    //==============================================================================================
    friend std::ostream& operator<<(std::ostream& os, eve::like<valder> auto const& z)
    {
      return os << std::setprecision(20) << "(" << val(z) << ", "<< der(z) << ")" << std::noshowpos;
    }

    //==============================================================================================
    //  val/der parts as functions
    //==============================================================================================

    /// Retrieve the value part of the current valder number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( flx::val_, eve::like<valder> auto&& z ) noexcept
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( flx::val_, eve::like<valder> auto const&& z ) noexcept
    {
      return get<0>(EVE_FWD(z));
   }

    /// Retrieve the derivative part of the current valder number
    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( flx::der_, eve::like<valder> auto&& z ) noexcept
    {
      return get<1>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend
    decltype(auto) tagged_dispatch( flx::der_, eve::like<valder> auto const&& z ) noexcept
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    // helpers
    //==============================================================================================
    // mask helper
    //==============================================================================================
    template<eve::conditional_expr Cond>
    static EVE_FORCEINLINE auto if_else_1(Cond const & cond)
    {
      if constexpr(Cond::has_alternative) return cond.rebase(1);
      else return cond.else_(1);
    }
    template<eve::conditional_expr Cond>
    static EVE_FORCEINLINE auto if_else_0(Cond const & cond)
    {
      if constexpr(Cond::has_alternative) return cond.rebase(0);
      else return cond.else_(0);
    }
    //==============================================================================================
    // Compute non-derivable function
    //==============================================================================================
    template<typename Func, typename Z1, typename... Zs>
    static EVE_FORCEINLINE auto compute(Func f, Z1 const& z1, Zs const& ... zs)
    {
      return f(val(z1), val(zs)...);
    }

    template<typename Func, eve::decorator D, typename Z1, typename... Zs>
    static EVE_FORCEINLINE auto compute(Func f, D const & , Z1 const& z1, Zs const& ... zs)
    {
      return D()(f)(val(z1), val(zs)...);
    }

    //==============================================================================================
    //  Unary functions
    //==============================================================================================
    template<typename Func, eve::like<valder> Z>
    static EVE_FORCEINLINE auto deriv(Func f, Z const & z)
    {
      auto [v, d] = z;
      return Z{f(v), flx::derivative(f)(v)*d};
    }

    template<typename Func, eve::decorator D, eve::like<valder> Z>
    static EVE_FORCEINLINE auto deriv(Func f, D const &, Z const & z)
    {
      auto [v, d] = z;
      return Z{D()(f)(v), flx::derivative(f)(v)*d};
    }

   template<typename Func, eve::conditional_expr C, eve::like<valder> Z>
    static EVE_FORCEINLINE auto deriv(Func f, C const & cond, Z const & z)
    {
      auto [v, d] = z;
      return Z{f[cond](v), flx::derivative(f[if_else_1(cond)])(v)*d};
      //        return Z{f[cond](v), derivative(f[          cond ])(v)*d};
    }

    template<typename Func, eve::conditional_expr C, eve::decorator D, eve::like<valder> Z>
    static EVE_FORCEINLINE auto deriv(Func f, C const & cond, D const &, Z const & z)
    {
      auto [v, d] = z;
      return Z{D()(f[cond])(v), flx::derivative(D()(f[if_else_1(cond)]))(v)*d};
    }

    //==============================================================================================
    //  n_ary functions
    //==============================================================================================
    template<typename Func, eve::decorator D, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, D const &, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      return deriv(D()(f), z0, z1, zs...);
    }

    template<typename Func, eve::conditional_expr C, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, C const & cond, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      using v_t = decltype(f(val(z0),val(z1),val(zs)...));
      using r_t = flx::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto ds = kumi::make_tuple(v_t(der(zs))...);

      v_t d = sum_of_prod ( kumi::apply(deriv_1st(f[if_else_1(cond)]),vs), v_t(der(z0))
                          , kumi::apply(deriv_2nd(f[if_else_0(cond)]),vs), v_t(der(z1))
                          );

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((d = fam(d, kumi::apply(deriv_nth<I+3>(f[if_else_0(cond)]),vs), get<I>(ds))),...);
      }(std::index_sequence_for<Vs...>{});

      return r_t{ kumi::apply(f[cond],vs), d};
    }

    template<typename Func, eve::conditional_expr C, eve::decorator D, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, C const & cond, D const &, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      using v_t = decltype(D()(f[cond])(val(z0),val(z1),val(zs)...));
      using r_t = flx::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto ds = kumi::make_tuple(v_t(der(zs))...);

      v_t d = sum_of_prod ( kumi::apply(deriv_1st(D()(f)[if_else_1(cond)]),vs), v_t(der(z0))
                          , kumi::apply(deriv_2nd(D()(f)[if_else_0(cond)]),vs), v_t(der(z1))
                          );

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((d = fam(d, kumi::apply(deriv_nth<I+3>(D()(f)[if_else_0(cond)]),vs), get<I>(ds))),...);
      }(std::index_sequence_for<Vs...>{});

      return r_t{ kumi::apply(D(f)[cond],vs), d};
    }

    template<typename Func, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, V0 const& z0, V1 const& z1, Vs const&... zs )
    {
      using v_t = decltype(f(val(z0),val(z1),val(zs)...));
      using r_t = flx::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto ds = kumi::make_tuple(v_t(der(zs))...);

      v_t d = sum_of_prod ( kumi::apply(deriv_1st(f),vs), v_t(der(z0))
                          , kumi::apply(deriv_2nd(f),vs), v_t(der(z1))
                          );

      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((d = fam(d, kumi::apply(deriv_nth<I+3>(f),vs), get<I>(ds))),...);
      }(std::index_sequence_for<Vs...>{});

      return r_t{ kumi::apply(f,vs), d};
    }

    // 2params to see why
    template<typename Func, typename V0, typename V1>
    static EVE_FORCEINLINE auto deriv(Func f, V0 const& z0, V1 const& z1 )
    {
      using v_t = decltype(f(val(z0),val(z1)));
      using r_t = flx::as_valder_t<v_t>;

      v_t d = sum_of_prod ( deriv_1st(f)(val(z0), val(z1)), v_t(der(z0))
                          , deriv_2nd(f)(val(z0), val(z1)), v_t(der(z1))
                          );
      return r_t{ f(val(z0), val(z1)), d};
    }
     //==============================================================================================
     //  Operators
     //==============================================================================================

     //==============================================================================================
     // add/sub
     //==============================================================================================
     EVE_FORCEINLINE friend auto& operator+= ( eve::like<valder> auto& self
                                             , eve::like<valder> auto const& other
                                             ) noexcept
     {
       val(self) += val(other);
       der(self) += der(other);
       return self;
     }

     EVE_FORCEINLINE friend auto& operator-= ( eve::like<valder> auto& self
                                             , eve::like<valder> auto const& other
                                             ) noexcept
     {
       val(self) -= val(other);
       der(self) -= der(other);
       return self;
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::sub_
                                                 , eve::like<valder> auto const & z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(sub(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       return r_t{v1-v2, d1-d2};
     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
 //                                                 , Z const & self
 //                                                 , O const & other
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = self;
 //       return Z{ a-other, b};
 //     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::sub_
 //                                                 , O const & a0
 //                                                 , Z const & a1
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = a1;
 //       return Z{ a0-a, -b};
 //     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::add_
                                                 , eve::like<valder> auto const & z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(add(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       return r_t{v1+v2, d1+d2};
     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
 //                                                 , Z const & self
 //                                                 , O const &  other
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = self;
 //       return Z{ a+other, b};
 //     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::add_
 //                                                 , O const & a0
 //                                                 , Z const & a1
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = a1;
 //       return Z{ a+a0, b};
 //     }

     template<eve::like<valder> Z> EVE_FORCEINLINE friend auto operator-(Z const & z) noexcept
     {
       return Z{-val(z), -der(z)};
     }

     template<eve::like<valder> Z> EVE_FORCEINLINE friend auto operator+(Z const &z) noexcept
     {
       return z;
     }

     //==============================================================================================
     // multiplies
     //==============================================================================================
     EVE_FORCEINLINE friend auto& operator*= ( eve::like<valder> auto  & self
                                             , eve::like<valder> auto  const & other
                                             ) noexcept
     {
       using r_t = std::remove_reference_t<decltype(self)>;
       auto [v1, d1] = self;
       auto [v2, d2] = other;
       auto dr = sum_of_prod(v1, d2, v2, d1);
       auto vr = v1*v2;
       return self = r_t(vr, dr);
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mul_
                                                 , eve::like<valder> auto const & z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(mul(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto dr = sum_of_prod(v1, d2, v2, d1);
       auto vr = v1*v2;
       return r_t(vr, dr);
     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto& operator *= ( Z & self
                                              , O const & other
                                              ) noexcept
     {
       auto [a, b] = self;
       return self = Z{ a*other, b*other};
     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
 //                                                 , Z const & a0
 //                                                 , O const & a1
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = a0;
 //       return Z{ a*a1, b*a1};
 //     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::mul_
 //                                                 , O const & a0
 //                                                 , Z const & a1
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = a1;
 //       return Z{a*a0, b*a0};
 //     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto operator*( Z const & a0
                                          , O const & a1
                                          ) noexcept
     {
       return mul(a0, a1);
     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto  operator*( O const & a0
                                           , Z const & a1
                                           ) noexcept
     {
       return mul(a1, a0);
     }

     //==============================================================================================
     // divide
     //==============================================================================================

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto operator/= ( Z & self
                                            , eve::like<valder> auto const& other
                                            ) noexcept
     {
       using r_t = std::remove_reference_t<decltype(self)>;
       auto [v1, d1] = self;
       auto [v2, d2] = other;
       auto dr = deriv_of_prod(v2, d1, v1, d2)/sqr(v2);
       auto vr = v1/v2;
       return self = r_t(vr, dr);
     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
 //                                                 , Z const & a0
 //                                                 , O const & a1
 //                                                 ) noexcept
 //     {
 //       auto [a, b] = a0;
 //       return Z{a/a1, b/a1};
 //     }

 //     template<eve::like<valder> Z, floating_real_value O>
 //     EVE_FORCEINLINE friend auto tagged_dispatch (  eve::tag::div_
 //                                                 , O const & a0
 //                                                 , Z const & a1
 //                                                 ) noexcept
 //     {
 //       auto [v1, d1] = a1;
 //       return Z{a0/v1, -a0*d1/sqr(v1)};
 //     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::div_
                                                 , eve::like<valder> auto z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(div(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto dr = diff_of_prod(v2, d1, v1, d2)/sqr(v2);
       auto vr = v1/v2;
       return r_t(vr, dr);
     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto operator/= ( Z & self
                                            , O const& other

                                            ) noexcept
     {
       auto [a, b] = self;
       return self = Z{ a/other, b/other};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rec_, Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto inv = eve::rec(v);
       return Z{inv, -eve::sqr(inv)*d};
     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto operator/( Z const & a0
                                          , O const & a1
                                          ) noexcept
     {
       return eve::div(a0, a1);
     }

     template<eve::like<valder> Z, eve::floating_real_value O>
     EVE_FORCEINLINE friend auto  operator/( O const & a0
                                           , Z const & a1
                                           ) noexcept
     {
       return eve::div(a0, a1);
     }

     //==============================================================================================
     // functions & constants
     //==============================================================================================
     // constants
     template<typename Tag, eve::like<valder> T>
     EVE_FORCEINLINE friend auto tagged_dispatch(Tag, eve::as<T> const&) noexcept
     {
       return T{ eve::detail::callable_object<Tag>{}(eve::as<value_type>{})};
     }

    //==============================================================================================
    // Functions support
    //==============================================================================================
//     template<typename Tag, eve::like<valder> Z>
//     EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const&, Z const& z) noexcept
//     ->    decltype(deriv(eve::detail::callable_object<Tag>(), z))
//     {
//       return deriv(eve::detail::callable_object<Tag>(), z);
//     }

//     template<typename Tag, eve::decorator D, eve::like<valder> Z>
//     EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const&, D const& d, Z const& z) noexcept
//     ->    decltype(deriv(eve::detail::callable_object<Tag>(), d, z))
//     {
//       return deriv(eve::detail::callable_object<Tag>(), d, z);
//     }


     //==============================================================================================
     // unary functions
     template<typename Tag>
     EVE_FORCEINLINE friend auto tagged_dispatch(Tag, eve::like<valder> auto const& v) noexcept
     requires( has_derivation_v<Tag> )
     {
       if constexpr(is_derivable_v<Tag>) return deriv( eve::detail::callable_object<Tag>{}, v);
       else                              return compute( eve::detail::callable_object<Tag>{}, v);
     }

     //==============================================================================================
     // n-ary functions
     template<typename Tag>
     EVE_FORCEINLINE friend auto tagged_dispatch (Tag, eve::like<valder> auto const&... v) noexcept
     requires( has_derivation_v<Tag> )
     {
       if constexpr(is_derivable_v<Tag>) return deriv( eve::detail::callable_object<Tag>{}, v...);
       else                              return compute( eve::detail::callable_object<Tag>{}, v...);
     }

     // lpnorm

     // specials cases
     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::exponent_, Z const& z) noexcept
     {
       return exponent(val(z));
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::mantissa_, Z const& z) noexcept
     {
       return Z{mantissa(val(z)), der(z)};
     }

     //==============================================================================================/////////////////////////
     //==  peculiar cases
     //==============================================================================================/////////////////////////
     template<eve::like<valder> Z, eve::value N>
     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ldexp_
                                                 , Z const& z,  N const& n) noexcept
     {
       return Z{ldexp(val(z), val(n)), ldexp(one(as(val(z))), val(n))*der(z)};
     }


     //==============================================================================================/////////////////////////
     //==  optimizations
     //==============================================================================================/////////////////////////
     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::cbrt_, Z const& z) noexcept
     {
       auto [v, d] = z;
       auto cb = cbrt(v);
       return Z{cb, eve::rec(3*sqr(cb))*d};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cos_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sincos(v);
       return Z{c, -d*s};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosh_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinhcosh(v);
       return Z{c, d*s};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sqrt_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto sqrtv = eve::sqrt(v);
       return Z{sqrtv, d/(2*sqrtv)};
     }

  template<eve::like<valder> Z>
  EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp_, Z const& z ) noexcept
  {
     auto [v, d] = z;
     auto e = eve::exp(v);
    return Z{e, e*d};
  }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp2_, Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto e = eve::exp2(v);
       return Z{e, e*log_2(as(v))*d};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::exp10_, Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto e = eve::exp10(v);
       return Z{e, e*log_10(as(v))*d};
     }

     //==============================================================================================
     //  Binary functions
     //==============================================================================================

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2_
                                                 , eve::like<valder> auto const& z1
                                                 , eve::like<valder> auto const& z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::atan2(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
       return r_t{eve::atan2(v1, v2), invden*sum_of_prod(v1, d2, v2, d1)};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2d_
                                                 , eve::like<valder> auto const& z1
                                                 , eve::like<valder> auto const& z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::atan2d(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
       return r_t{atan2d(v1, v2), radindeg(invden*sum_of_prod(v1, d2, v2, d1))};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::atan2pi_
                                                 , eve::like<valder> auto const& z1
                                                 , eve::like<valder> auto const& z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::atan2pi(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto  invden = rec(sum_of_prod(v1, v1, v2, v2));
       return r_t{eve::atan2pi(v1, v2), radinpi(invden*sum_of_prod(v1, d2, v2, d1))};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::dist_
                                                 , eve::like<valder> auto const& z1
                                                 , eve::like<valder> auto const& z2
                                                 ) noexcept
     {
       using v_t = decltype(dist(val(z1), val(z2)));
       using r_t = flx::as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto  s = sign(v1-v2);
       return r_t{dist(v1, v2), s*(d1-d2)};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::ulpdist_
                                                 , eve::like<valder> auto const& z1
                                                 , eve::like<valder> auto const& z2
                                                 ) noexcept
     {
       return eve::max( eve::ulpdist(val(z1), val(z2))
                      , eve::ulpdist(der(z1), der(z2)));
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                 , eve::like<valder> auto const & z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::pow(val(z1), val(z2)));
       using r_t = as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto  puv = eve::pow(v1, v2);
       return r_t{puv, puv*sum_of_prod(v2/v1, d1, eve::log(v1), d2)};
     }

    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                 , eve::like<valder> auto const & z1
                                                 , eve::floating_real_value auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::pow(val(z1), val(z2)));
       using r_t = as_valder_t<v_t>;
       auto v1 = v_t(val(z1)); auto d1 = v_t(der(z1));
       auto  p = eve::pow(v1, z2);
       return r_t{p, p*(z2/v1)*d1};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::pow_
                                                 , eve::floating_real_value auto const & z1
                                                 , eve::like<valder> auto const & z2
                                                 ) noexcept
     {
       using v_t = decltype(eve::pow(val(z1), val(z2)));
       using r_t = as_valder_t<v_t>;
       auto v2 = v_t(val(z2)); auto d2 = v_t(der(z2));
       auto p = eve::pow(z1, v2);
       return r_t{p, eve::log(z1)*p*d2};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cosd_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sindcosd(v);
       return Z{c, -d*eve::deginrad(s)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cospi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinpicospi(v);
       return Z{c, -d*s*eve::pi(as(v))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::csc_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto cs = eve::csc(v);
       return Z{cs, -d*cs*eve::cot(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cscd_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto cs = eve::cscd(v);
       return Z{cs, -d*eve::radindeg(cs)*eve::cotd(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::csch_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto cs = eve::csch(v);
       return Z{cs, -d*cs*eve::coth(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::cscpi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto cs = eve::cscpi(v);
       return Z{cs, -d*cs*eve::cotpi(v)*eve::pi(as(v))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::rsqrt_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto rs = eve::rsqrt(v);
       return Z{rs, d*eve::mhalf(eve::as(v))*rs*eve::rec(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sec_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto se = eve::sec(v);
       return Z{se, d*se*eve::tan(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::secd_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto se = secd(v);
       return Z{se, d*radindeg(se)*tand(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sech_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto se = eve::sech(v);
       return Z{se, -d*se*eve::tanh(v)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::secpi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto se = eve::secpi(v);
       return Z{se, d*se*eve::tanpi(v)*eve::pi(as(v))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sin_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sincos(v);
       return Z{s, d*c};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sincos_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sincos(v);
       return kumi::tuple{Z{s, d*c}, Z{c, -d*s}};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpicospi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinpicospi(v);
       auto fac = eve::pi(as(v));
       return kumi::tuple{Z{s, d*c*fac}, Z{c, -d*s*fac}};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinpi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinpicospi(v);
       return Z{s, d*c*eve::pi(as(v))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sindcosd_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= sindcosd(v);
       auto fac = deginrad(d);
       return kumi::tuple{Z{s, c*fac}, Z{c, -s*fac}};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sind_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sindcosd(v);
       return Z{s, d*eve::deginrad(c)};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinhcosh_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinhcosh(v);
       return kumi::tuple{Z{s, d*c}, Z{c, d*s}};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::sinh_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto [s, c]= eve::sinhcosh(v);
       return Z{s, d*c};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tan_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto t = eve::tan(v);
       return Z{t, d*eve::inc(eve::sqr(t))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanpi_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto t = eve::tanpi(v);
       return Z{t, d*eve::inc(eve::sqr(t))*eve::pi(as(v))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tand_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto t = eve::tand(v);
       return Z{t, eve::deginrad(d)*inc(eve::sqr(t))};
     }

     template<eve::like<valder> Z>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::tanh_
                                                , Z const& z ) noexcept
     {
       auto [v, d] = z;
       auto t = tanh(v);
       return Z{t, oneminus(sqr(t))*d};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::modf_
                                                , eve::like<valder> auto const& z ) noexcept
     {
       return kumi::tuple{frac(z), trunc(z)};
     }

     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
                                                , auto const & c
                                                , eve::like<valder> auto const& a
                                                , eve::like<valder> auto const& b ) noexcept
     {
       auto va = val(a); auto da = der(a);
       auto vb = val(b); auto db = der(b);
       auto vc = c; //val(c);
       using v_t = decltype(eve::if_else(vc, va, vb));
       using r_t = as_valder_t<v_t>;
       return r_t{eve::if_else(vc, va, vb), eve::if_else(vc, da, db)};
     }

     template < eve::like < valder> Z2, eve::generator < typename Z2::value_type> Constant>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
                                                , auto const & c
                                                , Constant const& a
                                                , Z2 const& b ) noexcept
     {
       auto vb = val(b); auto db = der(b);
       auto vc = c; //val(c);
       using v_t = decltype(eve::if_else(vc, a, vb));
       using r_t = as_valder_t<v_t>;
       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
     }

     template < eve::like < valder> Z1, eve::generator < typename Z1::value_type> Constant>
     EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::if_else_
                                                , auto const & c
                                                , Z1 const& b
                                                , Constant const& a

                                                ) noexcept
     {
       auto vb = val(b); auto db = der(b);
       auto vc = c; //val(c);
       using v_t = decltype(eve::if_else(vc, a, vb));
       using r_t = as_valder_t<v_t>;
       return r_t{eve::if_else(vc, a, vb), eve::if_else(vc, eve::zero, db)};
     }



 //     EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::nthroot_
 //                                                 , eve::like<valder> auto  const& z
 //                                                 , eve::like<valder> auto  const& n) noexcept
 //     {
 //       EVE_ASSERT(eve::all(is_flint(n)),  "n is not flint");
 //       auto v1 = val(z); auto d1 = der(z);
 //       auto v2 = val(n); auto d2 = der(n);
 //       auto rn = nthroot(v1, v2);
 //       using v_t =  decltype(rn);
 //       using elt_t = element_type_t<v_t>;
 //       auto fn = rec(convert(n, as<elt_t>()));
 //       using r_t = as_valder_t<v_t>;
 //       return r_t{rn, rn*fn*sum_of_prod(d1, rec(v1), minus(d2), log(v1)*fn)};
 //     }

  };
  //================================================================================================
  //! @}
  //================================================================================================
}
