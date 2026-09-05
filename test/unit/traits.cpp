//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <test.hpp>

template<typename T> using wide_of = eve::wide<T>;

template<typename B, typename H>
using widened = eve::wide<H, eve::fixed<eve::cardinal_v<wide_of<B>>>>;

// Through a variable template, so that a pack with no common type is a false and not an error.
template<typename... Ts>
constexpr bool mixes                   = requires { typename flx::as_hyperdual<Ts...>::type; };

template<unsigned int Ord> using order = std::integral_constant<unsigned int, Ord>;
using orders                           = tts::types<order<1>, order<2>, order<3>, order<4>>;

TTS_CASE_TPL("A base value joins the algebra it meets", orders)
<typename O>(tts::type<O>)
{
  using hd = flx::hyperdual<double, O::value>;
  using hf = flx::hyperdual<float, O::value>;

  TTS_TYPE_IS((flx::as_hyperdual_t<double, hd>), hd);
  TTS_TYPE_IS((flx::as_hyperdual_t<hd, double>), hd);
  TTS_TYPE_IS((flx::as_hyperdual_t<float, hf>), hf);
  TTS_TYPE_IS((flx::as_hyperdual_t<hf, float>), hf);
  TTS_TYPE_IS((flx::as_hyperdual_t<int, hd>), hd);

  TTS_TYPE_IS((flx::as_hyperdual_t<float, hd>), hd);
  TTS_TYPE_IS((flx::as_hyperdual_t<double, hf>), hf);

  TTS_TYPE_IS((flx::as_hyperdual_t<wide_of<double>, hd>), (widened<double, hd>));
  TTS_TYPE_IS((flx::as_hyperdual_t<wide_of<float>, hf>), (widened<float, hf>));
  TTS_TYPE_IS((flx::as_hyperdual_t<widened<double, hd>, double>), (widened<double, hd>));
  TTS_TYPE_IS((flx::as_hyperdual_t<widened<double, hd>, wide_of<double>>), (widened<double, hd>));

  TTS_CONSTEXPR_EXPECT_NOT((mixes<wide_of<float>, hd>));
  TTS_CONSTEXPR_EXPECT_NOT((mixes<wide_of<double>, hf>));

  TTS_CONSTEXPR_EQUAL(eve::cardinal_v<hd>, 1);
};

// The smallest order wins: an operand of order two carries no third derivative, and filling one
// with zeros would claim what it never said.
template<unsigned int M, unsigned int N> void narrowing()
{
  using lo = flx::hyperdual<double, (M < N ? M : N)>;

  TTS_TYPE_IS((flx::as_hyperdual_t<flx::hyperdual<double, M>, flx::hyperdual<double, N>>), lo);
  TTS_TYPE_IS((flx::as_hyperdual_t<flx::hyperdual<double, N>, flx::hyperdual<double, M>>), lo);
  TTS_TYPE_IS(
      (flx::as_hyperdual_t<widened<double, flx::hyperdual<double, M>>, flx::hyperdual<double, N>>),
      (widened<double, lo>));
}

TTS_CASE("Two algebras of different orders meet at the smaller one")
{
  narrowing<1, 2>();
  narrowing<1, 4>();
  narrowing<2, 3>();
  narrowing<3, 4>();
  narrowing<4, 4>();
};

TTS_CASE("Base values alone are read at the widest order")
{
  TTS_TYPE_IS((flx::as_hyperdual_t<double, double>), (flx::hyperdual<double, flx::max_order>));
  TTS_TYPE_IS((flx::as_hyperdual_t<float, float>), (flx::hyperdual<float, flx::max_order>));
  TTS_TYPE_IS((flx::as_hyperdual_t<wide_of<double>, double>),
              (widened<double, flx::hyperdual<double, flx::max_order>>));
};

TTS_CASE("Two arguments have to agree on their element and on their lanes")
{
  TTS_CONSTEXPR_EXPECT((mixes<wide_of<double>, flx::hyperdual<double, 2>>));
  TTS_CONSTEXPR_EXPECT_NOT((mixes<wide_of<double>, wide_of<float>>));
  TTS_CONSTEXPR_EXPECT((mixes<widened<double, flx::hyperdual<double, 2>>, wide_of<double>>));
  TTS_CONSTEXPR_EXPECT_NOT((mixes<widened<float, flx::hyperdual<double, 2>>, wide_of<float>>));
  TTS_CONSTEXPR_EXPECT_NOT((mixes<flx::hyperdual<double, 2>, flx::hyperdual<float, 2>>));
  TTS_CONSTEXPR_EXPECT_NOT(
      (mixes<widened<float, flx::hyperdual<float, 2>>, flx::hyperdual<double, 2>>));
};

template<typename A, typename B> void follows_eve()
{
  constexpr bool eve_says = requires { eve::add(std::declval<A>(), std::declval<B>()); };

  TTS_EXPECT((mixes<A, B>) == eve_says);

  if constexpr(eve_says)
  {
    using from_eve = decltype(eve::add(std::declval<A>(), std::declval<B>()));
    using ours     = flx::as_hyperdual_t<A, B>;

    TTS_TYPE_IS((eve::as_floating_point_t<eve::underlying_type_t<from_eve>>),
                (eve::underlying_type_t<ours>));
    TTS_EXPECT(eve::cardinal_v<from_eve> == eve::cardinal_v<ours>);
  }
}

template<typename A, typename... Ts> void row() { (follows_eve<A, Ts>(), ...); }
template<typename... Ts> void             square() { (row<Ts, Ts...>(), ...); }

TTS_CASE("Every pair of base values answers what EVE answers")
{
  square<double,
         float,
         int,
         wide_of<double>,
         wide_of<float>,
         eve::wide<double, eve::fixed<1>>,
         eve::wide<double, eve::fixed<4>>,
         eve::wide<float, eve::fixed<2>>>();
};

TTS_CASE("The rule fluxion does not follow")
{
  // EVE brings a lone double down to float against a wide of floats. The refusals above decline to
  // do that to an algebra, and this stops compiling the day EVE declines it too.
  wide_of<float> w {};
  double         d {};

  TTS_EXPECT_COMPILES(w, d, { eve::add(w, d); });
};
