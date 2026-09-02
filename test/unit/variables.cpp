//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

#include <iostream>

// Seeding a variable is the whole entry point into a derivative: the value goes in the constant
// slot and a one goes in front of every nilpotent unit that variable is differentiated along. Which
// unit belongs to whom is what variables<Is...> says, and the component index says it back: bit i
// of the index means the component carries unit i, so unit i reads at component 1 << i.
static_assert(std::same_as<decltype(flx::variable<2>(1.0)), flx::hyperdual<double, 2>>);
static_assert(std::same_as<decltype(flx::variables<0, 1>(1.0, 2.0)),
                           kumi::tuple<flx::hyperdual<double, 2>, flx::hyperdual<double, 2>>>);

// An argument nobody asked to differentiate comes back untouched, at its own type
static_assert(std::same_as<decltype(flx::variables<0>(1.0, 2.0)),
                           kumi::tuple<flx::hyperdual<double, 1>, double>>);

// The order is how many derivations were asked for, so a lone value differentiated twice is order 2
static_assert(
    std::same_as<decltype(flx::variables<0, 0>(1.0)), kumi::tuple<flx::hyperdual<double, 2>>>);

int main()
{
  int  broken = 0;
  auto check  = [ & ](bool ok, auto what)
  {
    if(!ok)
    {
      std::cerr << "failed: " << what << "\n";
      ++broken;
    }
  };

  // One variable, all the units, which is the constructor's tag spelled with the type deduced
  auto single = flx::variable<2>(2.5);
  check(get<0>(single) == 2.5, "value of a single variable");
  check(get<1>(single) == 1.0, "unit 0 of a single variable");
  check(get<2>(single) == 1.0, "unit 1 of a single variable");
  check(get<3>(single) == 0.0, "cross part of a single variable");

  // Two variables, one unit each: x takes unit 0, y takes unit 1, and their cross part stays empty
  auto [ x, y ] = flx::variables<0, 1>(10.0, -2.3);
  check(get<0>(x) == 10.0, "value of the first of two variables");
  check(get<1>(x) == 1.0, "unit 0 belongs to the first");
  check(get<2>(x) == 0.0, "unit 1 does not belong to the first");
  check(get<0>(y) == -2.3, "value of the second of two variables");
  check(get<1>(y) == 0.0, "unit 0 does not belong to the second");
  check(get<2>(y) == 1.0, "unit 1 belongs to the second");

  // Two derivations for the first argument and one for the second, the third left alone
  auto [ a, b, c ] = flx::variables<0, 0, 1>(1.5, 2.5, 3.5);
  check(get<1>(a) == 1.0 && get<2>(a) == 1.0, "the first argument takes units 0 and 1");
  check(get<4>(a) == 0.0, "and not unit 2");
  check(get<4>(b) == 1.0, "the second argument takes unit 2");
  check(get<1>(b) == 0.0 && get<2>(b) == 0.0, "and neither of the first two");
  check(c == 3.5, "an argument nobody differentiates is passed through");

  // The same seeding on a wide, which the type computation reaches through untouched
  auto broad = flx::variable<2>(eve::wide<double> {2.5});
  static_assert(std::same_as<decltype(broad), eve::wide<flx::hyperdual<double, 2>>>);
  check(eve::all(get<0>(broad) == 2.5), "value of a wide variable");
  check(eve::all(get<1>(broad) == 1.0), "unit 0 of a wide variable");
  check(eve::all(get<3>(broad) == 0.0), "cross part of a wide variable");

  return broken;
}
