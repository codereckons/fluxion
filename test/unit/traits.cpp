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

  // A narrower base is taken up by the wider one it is mixed with
  static_assert(std::same_as<flx::as_hyperdual_t<float, hd>, hd>);

  // A wide argument installs its cardinal, and the hyperdual becomes a structure of arrays
  static_assert(std::same_as<flx::as_hyperdual_t<wide_of<double>, hd>, widened<double, hd>>);
  static_assert(std::same_as<flx::as_hyperdual_t<wide_of<float>, hf>, widened<float, hf>>);

  // A cardinal already carried by one argument survives meeting a scalar one
  static_assert(
      std::same_as<flx::as_hyperdual_t<widened<double, hd>, double>, widened<double, hd>>);
  static_assert(
      std::same_as<flx::as_hyperdual_t<widened<double, hd>, wide_of<double>>, widened<double, hd>>);
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

// Two genuinely wide arguments of different lane counts have no common type, and saying so beats
// picking one of the two counts. The trait answers by having no member, so the question is asked
// through a variable template, where the pack stays dependent and the absence is a false rather
// than an error.
template<typename... Ts>
constexpr bool mixes = requires { typename flx::as_hyperdual<Ts...>::type; };

static_assert(mixes<wide_of<double>, flx::hyperdual<double, 2>>);
static_assert(!mixes<wide_of<double>, wide_of<float>>);

int main() { return 0; }
