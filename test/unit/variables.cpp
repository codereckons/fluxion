//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <test.hpp>

TTS_CASE("Seeding a variable names the units it is differentiated along")
{
  // variables<Is...> hands out the units, one index per argument, and unit i reads at component
  // 1 << i.
  TTS_TYPE_IS((decltype(flx::variable<2>(1.0))), (flx::hyperdual<double, 2>));
  TTS_TYPE_IS((decltype(flx::variables<0, 1>(1.0, 2.0))),
              (kumi::tuple<flx::hyperdual<double, 2>, flx::hyperdual<double, 2>>));

  TTS_TYPE_IS((decltype(flx::variables<0>(1.0, 2.0))),
              (kumi::tuple<flx::hyperdual<double, 1>, double>));

  TTS_TYPE_IS((decltype(flx::variables<0, 0>(1.0))), (kumi::tuple<flx::hyperdual<double, 2>>));
};

TTS_CASE("One variable takes every unit")
{
  auto single = flx::variable<2>(2.5);

  TTS_EQUAL(get<0>(single), 2.5);
  TTS_EQUAL(get<1>(single), 1.0);
  TTS_EQUAL(get<2>(single), 1.0);
  TTS_EQUAL(get<3>(single), 0.0);
};

TTS_CASE("Two variables take one unit each")
{
  auto [ x, y ] = flx::variables<0, 1>(10.0, -2.3);

  TTS_EQUAL(get<0>(x), 10.0);
  TTS_EQUAL(get<1>(x), 1.0);
  TTS_EQUAL(get<2>(x), 0.0);
  TTS_EQUAL(get<0>(y), -2.3);
  TTS_EQUAL(get<1>(y), 0.0);
  TTS_EQUAL(get<2>(y), 1.0);
};

TTS_CASE("An argument takes as many units as it was named times")
{
  auto [ a, b, c ] = flx::variables<0, 0, 1>(1.5, 2.5, 3.5);

  TTS_EQUAL(get<1>(a), 1.0);
  TTS_EQUAL(get<2>(a), 1.0);
  TTS_EQUAL(get<4>(a), 0.0);
  TTS_EQUAL(get<4>(b), 1.0);
  TTS_EQUAL(get<1>(b), 0.0);
  TTS_EQUAL(get<2>(b), 0.0);
  TTS_EQUAL(c, 3.5);
};

TTS_CASE("A wide is seeded the same way")
{
  auto broad = flx::variable<2>(eve::wide<double> {2.5});

  TTS_TYPE_IS((decltype(broad)), (eve::wide<flx::hyperdual<double, 2>>));
  TTS_EQUAL(get<0>(broad), eve::wide<double> {2.5});
  TTS_EQUAL(get<1>(broad), eve::wide<double> {1.0});
  TTS_EQUAL(get<3>(broad), eve::wide<double> {0.0});
};
