//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

// What a mixed pack of arguments computes in. Nothing here runs: the whole subject is the type the
// traits arrive at, so a green build is the whole result. Cardinals are written as the cardinal of
// the matching wide rather than as a number, the CI building for SSE and for AVX2 alike.
template<typename T> using wide_of = eve::wide<T>;
template<typename B, typename H>
using widened = eve::wide<H, eve::fixed<eve::cardinal_v<wide_of<B>>>>;

// A pack with no common type answers by having no member, so the question is asked through a
// variable template, where the pack stays dependent and the absence is a false rather than an
// error.
template<typename... Ts>
constexpr bool                  mixes = requires { typename flx::as_hyperdual<Ts...>::type; };

template<unsigned int Ord> void mixing()
{
  using hd = flx::hyperdual<double, Ord>;
  using hf = flx::hyperdual<float, Ord>;

  // A base value carries no order of its own, so it never narrows the one it meets, and it says
  // nothing about the algebra either: what comes back is the hyperdual, unchanged.
  static_assert(std::same_as<flx::as_hyperdual_t<double, hd>, hd>);
  static_assert(std::same_as<flx::as_hyperdual_t<hd, double>, hd>);
  static_assert(std::same_as<flx::as_hyperdual_t<float, hf>, hf>);
  static_assert(std::same_as<flx::as_hyperdual_t<hf, float>, hf>);

  // An integer reaches the algebra through its floating point counterpart
  static_assert(std::same_as<flx::as_hyperdual_t<int, hd>, hd>);

  // A lone scalar converts into whatever it is mixed with, in either direction, the way it converts
  // into a wide under EVE. There is no wider of the two to pick: EVE promotes nothing between
  // element types, so what the pack computes in is the algebra it was handed.
  static_assert(std::same_as<flx::as_hyperdual_t<float, hd>, hd>);
  static_assert(std::same_as<flx::as_hyperdual_t<double, hf>, hf>);

  // A wide argument installs its cardinal, and the hyperdual becomes a structure of arrays
  static_assert(std::same_as<flx::as_hyperdual_t<wide_of<double>, hd>, widened<double, hd>>);
  static_assert(std::same_as<flx::as_hyperdual_t<wide_of<float>, hf>, widened<float, hf>>);

  // A cardinal already carried by one argument survives meeting a scalar one
  static_assert(
      std::same_as<flx::as_hyperdual_t<widened<double, hd>, double>, widened<double, hd>>);
  static_assert(
      std::same_as<flx::as_hyperdual_t<widened<double, hd>, wide_of<double>>, widened<double, hd>>);

  // A wide states what its lanes are made of and converts to nothing, so meeting an algebra of
  // another element is a refusal rather than a choice between the two. That is what EVE itself
  // answers when two wides of different elements meet, at any width.
  static_assert(!mixes<wide_of<float>, hd>);
  static_assert(!mixes<wide_of<double>, hf>);
}

template void                                 mixing<1>();
template void                                 mixing<2>();
template void                                 mixing<3>();
template void                                 mixing<4>();

// The order of a mixed pack is the smallest of them, where kyosu takes the largest of its
// dimensions. An operand of order two carries no information of order three, and embedding it in a
// wider algebra would fill the missing derivatives with zeros, which claims something the operand
// never said.
template<unsigned int M, unsigned int N> void narrowing()
{
  using lo = flx::hyperdual<double, (M < N ? M : N)>;
  static_assert(
      std::same_as<flx::as_hyperdual_t<flx::hyperdual<double, M>, flx::hyperdual<double, N>>, lo>);
  static_assert(
      std::same_as<flx::as_hyperdual_t<flx::hyperdual<double, N>, flx::hyperdual<double, M>>, lo>);

  // and the cardinal is orthogonal to it: narrowing the order leaves the lanes alone
  static_assert(std::same_as<flx::as_hyperdual_t<widened<double, flx::hyperdual<double, M>>,
                                                 flx::hyperdual<double, N>>,
                             widened<double, lo>>);
}

template void narrowing<1, 2>();
template void narrowing<1, 4>();
template void narrowing<2, 3>();
template void narrowing<3, 4>();
template void narrowing<4, 4>();

// Base values alone name no order, so the pack is read at the widest the library carries. That is
// the same rule as above seen from its other end: order_v of a base value is max_order.
static_assert(
    std::same_as<flx::as_hyperdual_t<double, double>, flx::hyperdual<double, flx::max_order>>);
static_assert(
    std::same_as<flx::as_hyperdual_t<float, float>, flx::hyperdual<float, flx::max_order>>);
static_assert(std::same_as<flx::as_hyperdual_t<wide_of<double>, double>,
                           widened<double, flx::hyperdual<double, flx::max_order>>>);

// Two genuinely wide arguments have to agree on their element, and on how many lanes they carry
static_assert(mixes<wide_of<double>, flx::hyperdual<double, 2>>);
static_assert(!mixes<wide_of<double>, wide_of<float>>);
static_assert(mixes<widened<double, flx::hyperdual<double, 2>>, wide_of<double>>);
static_assert(!mixes<widened<float, flx::hyperdual<double, 2>>, wide_of<float>>);

// Two hyperduals that disagree on what their components are made of have no common type either, for
// the same reason: nothing promotes a float algebra into a double one.
static_assert(!mixes<flx::hyperdual<double, 2>, flx::hyperdual<float, 2>>);
static_assert(!mixes<widened<float, flx::hyperdual<float, 2>>, flx::hyperdual<double, 2>>);

// EVE decides what a pack of base values computes in, and fluxion has to answer the same thing:
// refusal for refusal, then the same element and the same number of lanes. The one step of its own
// is to a floating point element, there being no algebra of integers here.
template<typename A, typename B> void follows_eve()
{
  constexpr bool eve_says = requires { eve::add(std::declval<A>(), std::declval<B>()); };
  static_assert(mixes<A, B> == eve_says);

  if constexpr(eve_says)
  {
    using from_eve = decltype(eve::add(std::declval<A>(), std::declval<B>()));
    using ours     = flx::as_hyperdual_t<A, B>;

    static_assert(std::same_as<eve::as_floating_point_t<eve::underlying_type_t<from_eve>>,
                               eve::underlying_type_t<ours>>);
    static_assert(eve::cardinal_v<from_eve> == eve::cardinal_v<ours>);
  }
}

template<typename... Ts> struct list
{
};
template<typename A, typename L> struct row;
template<typename A, typename... Ts> struct row<A, list<Ts...>>
{
  static void run() { (follows_eve<A, Ts>(), ...); }
};
template<typename L> struct square;
template<typename... Ts> struct square<list<Ts...>>
{
  static void run() { (row<Ts, list<Ts...>>::run(), ...); }
};

// Odd cardinals as well as the natural ones, so that the lanes are read and not guessed
using bases = list<double,
                   float,
                   int,
                   wide_of<double>,
                   wide_of<float>,
                   eve::wide<double, eve::fixed<1>>,
                   eve::wide<double, eve::fixed<4>>,
                   eve::wide<float, eve::fixed<2>>>;

// A hyperdual counts as a scalar where the lanes are counted, its cardinal being one, and as a wide
// where the element is read. So it takes the lanes of a wide it meets, and refuses its element.
template<unsigned int Ord> void hyperdual_roles()
{
  using hd = flx::hyperdual<double, Ord>;

  static_assert(eve::cardinal_v<hd> == 1);
  static_assert(mixes<wide_of<double>, hd>);
  static_assert(!mixes<wide_of<float>, hd>);
}

template void hyperdual_roles<1>();
template void hyperdual_roles<4>();

// The rule fluxion does not follow, pinned here so that it stops being a claim: EVE takes a lone
// double into a wide of floats and brings it down to float. Carried over to hyperduals it would
// bring an algebra of doubles down the same way, which is why the refusal above is a decision and
// not an oversight. Should EVE ever stop accepting this, the sentence needs rewriting, and this
// says so instead of letting it quietly become false.
static_assert(requires { eve::add(std::declval<wide_of<float>>(), std::declval<double>()); });

int main()
{
  square<bases>::run();
  return 0;
}
