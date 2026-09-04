//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <test.hpp>

#include <sstream>

// Through a template: a requirement that can never hold, with nothing left to substitute, is ill
// formed rather than false.
template<unsigned int Ord, typename T>
constexpr bool restrictable = requires(T h) { flx::restrict_to<Ord>(h); };

TTS_CASE("An order converts down and never up")
{
  // Bit i of a component index says the component carries unit i, so an order 2 is the first
  // four components of an order 3: a prefix, not a truncation that lands well.
  TTS_CONSTEXPR_EXPECT_NOT(
      (std::is_constructible_v<flx::hyperdual<double, 3>, flx::hyperdual<double, 2>>));
  TTS_CONSTEXPR_EXPECT(
      (std::is_constructible_v<flx::hyperdual<double, 2>, flx::hyperdual<double, 3>>));

  TTS_CONSTEXPR_EXPECT((restrictable<2, flx::hyperdual<double, 3>>));
  TTS_CONSTEXPR_EXPECT_NOT((restrictable<4, flx::hyperdual<double, 3>>));
  TTS_CONSTEXPR_EXPECT_NOT((restrictable<0, flx::hyperdual<double, 3>>));
};

TTS_CASE("Constructing at a lower order keeps the components it shares")
{
  // One value per component, so a component read from the wrong index shows itself.
  flx::hyperdual<double, 3> full {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  flx::hyperdual<double, 2> half(full);
  TTS_EQUAL(get<0>(half), 1.0);
  TTS_EQUAL(get<1>(half), 2.0);
  TTS_EQUAL(get<2>(half), 3.0);
  TTS_EQUAL(get<3>(half), 4.0);

  flx::hyperdual<double, 1> quarter(full);
  TTS_EQUAL(get<0>(quarter), 1.0);
  TTS_EQUAL(get<1>(quarter), 2.0);

  flx::hyperdual<double, 2> assigned {};
  assigned = full;
  TTS_EQUAL(get<3>(assigned), 4.0);
};

TTS_CASE("What a restriction drops is what carries the units it lost")
{
  flx::hyperdual<double, 3> full {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  flx::hyperdual<double, 2> half(full);

  std::ostringstream        whole;
  std::ostringstream        part;

  whole << full;
  part << half;

  TTS_EQUAL(whole.str(), std::string {"1 + 2e1 + 3e2 + 4e12 + 5e3 + 6e13 + 7e23 + 8e123"});
  TTS_EQUAL(part.str(), std::string {"1 + 2e1 + 3e2 + 4e12"});
  TTS_EQUAL(whole.str().rfind(part.str(), 0), 0ULL);
};

TTS_CASE("restrict_to says the same thing as a function")
{
  flx::hyperdual<double, 3> full {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  TTS_TYPE_IS((decltype(flx::restrict_to<2>(full))), (flx::hyperdual<double, 2>));
  TTS_EQUAL(get<3>(flx::restrict_to<2>(full)), 4.0);
  TTS_EQUAL(get<1>(flx::restrict_to<1>(full)), 2.0);
};

TTS_CASE("The wide shape restricts through that function alone")
{
  // A wide is none of ours, so the restriction can only be a function.
  flx::hyperdual<double, 3>            full {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  eve::wide<flx::hyperdual<double, 3>> broad(full);

  TTS_TYPE_IS((decltype(flx::restrict_to<2>(broad))), (eve::wide<flx::hyperdual<double, 2>>));

  auto cut = flx::restrict_to<2>(broad);
  TTS_EQUAL(get<0>(cut), eve::wide<double> {1.0});
  TTS_EQUAL(get<3>(cut), eve::wide<double> {4.0});
};
