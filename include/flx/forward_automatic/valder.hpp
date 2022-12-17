//==================================================================================================
/*
  Fluxion - Post-Modern Automatic Derivation
  Copyright : Fluxion Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/generator.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/underlying_type.hpp>

#include <flx/forward_automatic/detail/core.hpp>
#include <flx/forward_automatic/detail/math.hpp>
#include <flx/forward_automatic/detail/polynomial.hpp>
#include <flx/forward_automatic/detail/special.hpp>
#include <flx/forward_automatic/is_derivable.hpp>
#include <flx/forward_automatic/traits.hpp>
#include <flx/forward_automatic/var.hpp>

#include <ostream>

namespace flx
{
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
  template<eve::scalar_value Type>
  struct valder
  {
    // Tuple interface
    using tuple_type      = kumi::tuple<Type, Type>;
    using is_product_type = void;
    tuple_type storage;

    template<std::size_t I>
    friend decltype(auto) get(valder& s) noexcept { return get<I>(s.storage); }

    template<std::size_t I>
    friend decltype(auto) get(valder const& s) noexcept { return get<I>(s.storage); }

    /// Base value type
    using underlying_type = eve::underlying_type_t<Type>;

    /// Default constructors
    EVE_FORCEINLINE valder() {}
    EVE_FORCEINLINE valder(Type val) noexcept : storage {val, Type(0)} {}
    EVE_FORCEINLINE valder(Type val, Type der) noexcept : storage {val, der} {}

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, eve::like<valder> auto const& z)
    {
      return os << "(" << get<0>(z) << " @" << get<1>(z) << ")";
    }

    //==============================================================================================
    // Constants support
    //==============================================================================================
    template<typename Tag, eve::like<valder> VD>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag, eve::as<VD> const&) noexcept
    {
      eve::detail::callable_object<Tag> cst;
      if constexpr( std::same_as<Tag, eve::tag::true__> || std::same_as<Tag, eve::tag::false__> )
        return cst(as(real(VD {})));
      else return VD {cst(eve::as<Type> {}), Type {0}};
    }

    //==============================================================================================
    //  functions support
    //==============================================================================================
    template<typename Tag, typename Z1>
    requires(eve::like<Z1, valder>)
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z1 const& z1) noexcept
                        -> decltype(detail::valder_unary_dispatch(tag, z1))
    {
      return detail::valder_unary_dispatch(tag, z1);
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
    // functions which do not have in fluxion an implemented derivative decorated version
    //==============================================================================================
    template<typename Func, typename Z1, typename... Zs>
    static EVE_FORCEINLINE auto compute(Func f, Z1 const& z1, Zs const& ... zs)
    {
      if constexpr(eve::decorator<Z1>)
        return compute(z1(f), val(zs)...);
      else if constexpr(eve::conditional_expr<Z1>)
        return compute(f[z1], val(zs)...);
      else
        return f(val(z1), val(zs)...);
    }

    //==============================================================================================
    //  Operators
    //==============================================================================================
    //==============================================================================================
    // +
    //==============================================================================================
    EVE_FORCEINLINE friend auto operator+(eve::like<valder> auto const& z) noexcept { return z; }

    template<eve::like<valder> Z1, eve::like<valder> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
      val(self) += val(o);
      if constexpr(is_valder_v<Z2>) der(self) += der(o);
      return self;
    }

    //==============================================================================================
    // -
    //==============================================================================================
    EVE_FORCEINLINE friend auto operator-(eve::like<valder> auto const& z) noexcept { return z; }

    template<eve::like<valder> Z1, eve::like<valder> Z2>
    EVE_FORCEINLINE friend auto& operator-=(Z1& self, Z2 const& o) noexcept
    {
      val(self) -= val(o);
      if constexpr(is_valder_v<Z2>) der(self) -= der(o);
      return self;
    }

    //==============================================================================================
    // *
    //==============================================================================================
    template<eve::like<valder> Z1, eve::like<valder> Z2>
    EVE_FORCEINLINE friend auto& operator*= (Z1& self, Z2 const& o) noexcept
    {
      if constexpr(is_valder_v<Z2>)
      {
        auto [vs, ds] = self;
        auto [vv, dv] = o;
        der(self)   = eve::sum_of_prod(vs, dv, ds, vv);
        val(self)  *= vv;
      }
      else
      {
        val(self) *= o;
        der(self) *= o;
      }

      return self;
    }

    //==============================================================================================
    // /
    //==============================================================================================
    template<eve::like<valder> Z1, eve::like<valder> Z2>
    EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
    {
      if constexpr(is_valder_v<Z2>)
      {
        auto [vs, ds] = self;
        auto [vv, dv] = o;
        auto invo2  = eve::rec(eve::sqr(vv));
        val(self)  /= vv;
        der(self)   = eve::diff_of_prod(vv, ds, vs, dv) * invo2;
      }
      else
      {
        val(self) /= o;
        der(self) /= o;
      }

      return self;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // automatic part
    ///////////////////////////////////////////////////////////////////////////////

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
    static EVE_FORCEINLINE auto deriv(Func f, D const &, V0 const& z0, V1 const& z1, Vs
                                      const&... zs )
    {
      return deriv(D()(f), z0, z1, zs...);
    }

    template<typename Func, eve::conditional_expr C, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, C const & c, V0 const& z0, V1 const& z1, Vs
                                      const&... zs )
    {
      return deriv(f[c], z0, z1, zs...);
    }

    template<typename Func, typename V0, typename V1, typename... Vs>
    static EVE_FORCEINLINE auto deriv(Func f, V0 const& z0, V1 const& z1 , Vs const&... zs)
      requires(!eve::conditional_expr<V0> && !eve::decorator<V0>)
    {
      using v_t = decltype(f(val(z0),val(z1),val(zs)...));
      using r_t = flx::as_valder_t<v_t>;

      auto vs = kumi::make_tuple(v_t(val(z0)),v_t(val(z1)),v_t(val(zs))...);
      auto tzs = kumi::make_tuple(zs...);

      auto snd0 = [&](auto z0){
        if constexpr(!eve::like<decltype(z0), valder>) return eve::zero(eve::as(val(z0)));
        else return kumi::apply(derivative_1st(f),vs);
      };
      auto snd1 = [&](auto z1){
        if constexpr(!eve::like<decltype(z1), valder>) return eve::zero(eve::as(val(z1)));
        else return kumi::apply(derivative_2nd(f),vs);
      };

      v_t d = eve::sum_of_prod ( v_t(snd0(z0)), v_t(der(z0)), v_t(snd1(z1)), v_t(der(z1))   );
      if constexpr(sizeof...(zs)!= 0)
      {
        [&]<std::size_t... I>(std::index_sequence<I...>)
        {
          auto ifam = [&d](auto b, auto c){
            if constexpr(!eve::floating_value<decltype(c)>) d = eve::fam(d, b, v_t(der(c)));
          };
          ((ifam(kumi::apply(derivative_nth<I+3>(f),vs), get<I>(tzs))),...);
        }(std::index_sequence_for<Vs...>{});
      }
      return r_t{ kumi::apply(f,vs), d};
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    //==============================================================================================
    // unary functions
    template<typename Tag>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag, eve::like<valder> auto const& v) noexcept
    requires( !has_optimized_derivative_v<Tag> )
    {
      if constexpr(is_derivable_v<Tag>) return deriv( eve::detail::callable_object<Tag>{}, v);
      else                              return compute( eve::detail::callable_object<Tag>{}, v);
    }

    template<typename Tag, eve::conditional_expr C>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag
                                               , C const & c
                                               , eve::like<valder> auto const& v) noexcept
    requires( !has_optimized_derivative_v<Tag> )
    {
      if constexpr(is_derivable_v<Tag>)
        return eve::detail::mask_op(c, eve::detail::callable_object<Tag>{}, v);
      else
        return compute( eve::detail::callable_object<Tag>{}, c, v);
    }

    template<typename Tag, eve::decorator D>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag
                                               , D const & d
                                               , eve::like<valder> auto const& v) noexcept
    requires( !has_optimized_derivative_v<Tag> )
    {
      if constexpr(is_derivable_v<Tag>)
        return deriv( eve::detail::callable_object<Tag>{}, d, v);
      else
        return compute(eve::detail::callable_object<Tag>{}, d, v);
    }

    //==============================================================================================
    // n-ary functions
    template<typename Tag, typename V0, typename ... Vs>
    EVE_FORCEINLINE friend auto tagged_dispatch (Tag, V0 const& v0, Vs const&... vs ) noexcept
    requires( !has_optimized_derivative_v<Tag>
              && (eve::like < V0, valder > || (eve::like < Vs, valder > ||...)))
    {
      if constexpr(is_derivable_v<Tag>)
        return deriv( eve::detail::callable_object<Tag>{}, v0, vs ...);
      else
        return compute( eve::detail::callable_object<Tag>{}, v0, vs ...);
    }

    template<typename Tag, eve::conditional_expr C, typename V0, typename ... Vs>
    EVE_FORCEINLINE friend auto
    tagged_dispatch (Tag const &, C const& c, V0 const& v0, Vs const&... vs ) noexcept
    requires( !has_optimized_derivative_v<Tag>
              && (eve::like < V0, valder > || (eve::like < Vs, valder > ||...)))
    {
      if constexpr(is_derivable_v<Tag>)
      {
        auto deri = [&](auto p0, auto ...ps)
          {
            eve::detail::callable_object<Tag> co{};
            return deriv(co, p0, ps ...);
          };

        return eve::detail::mask_op(c, deri, v0, vs ...);
      }
      else
      {
        auto compu = [&](auto p0, auto ...ps)
          {
            eve::detail::callable_object<Tag> co{};
            return compute(co, p0, ps ...);
          };

        return eve::detail::mask_op(c, compu, v0, vs ...);
      }
    }
  };

  //===== Binary dispatch
  template<typename Tag, typename Z1, typename Z2>
  requires( derivate<Z1> || derivate<Z2> )
  EVE_FORCEINLINE  auto tagged_dispatch(Tag const& tag, Z1 const& z1, Z2 const& z2) noexcept
                -> decltype(detail::valder_binary_dispatch(tag, z1, z2))
  {
    return detail::valder_binary_dispatch(tag, z1, z2);
  }

  //===== Comparisons
  template<typename T1, typename T2>
  EVE_FORCEINLINE auto operator==(T1 const& a, T2 const& b) noexcept -> decltype(val(a) == val(b))
  requires( derivate<T1> || derivate<T2> )
  {
    return val(a) == val(b);
  }

  template<typename T1, typename T2>
  EVE_FORCEINLINE auto operator!=(T1 const& a, T2 const& b) noexcept -> decltype(!(a==b))
  requires( derivate<T1> || derivate<T2> )
  {
    return !(a == b);
  }

  //===== Ternary dispatch
  template<typename Tag, typename T1, typename T2, typename T3>
  requires(derivate<T1> || derivate<T2> || derivate<T3> )
  EVE_FORCEINLINE   auto tagged_dispatch ( Tag const& tag
                                         , T1 const& z1, T2 const& z2, T3 const& z3
                                         ) noexcept
                ->  decltype(detail::valder_ternary_dispatch(tag, z1, z2, z3))
  {
    return detail::valder_ternary_dispatch(tag, z1, z2, z3);
  }
}

//==================================================================================================
// Tuple interface
//==================================================================================================
template<typename T>
struct std::tuple_size<flx::valder<T>> : std::integral_constant<std::size_t,2> {};

template <std::size_t I, typename T>
struct std::tuple_element<I, flx::valder<T>> { using type = T; };
