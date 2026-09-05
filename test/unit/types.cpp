//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <test.hpp>

#include <sstream>

TTS_CASE_TPL("A hyperdual carries two components per order", flx::scalar_real_types)
<typename T>(tts::type<T>)
{
  TTS_CONSTEXPR_EQUAL((flx::hyperdual<T, 1>::static_dimension), 2);
  TTS_CONSTEXPR_EQUAL((flx::hyperdual<T, 2>::static_dimension), 4);
  TTS_CONSTEXPR_EQUAL((flx::hyperdual<T, 3>::static_dimension), 8);
  TTS_CONSTEXPR_EQUAL((flx::hyperdual<T, 4>::static_dimension), 16);

  TTS_CONSTEXPR_EQUAL((std::tuple_size<flx::hyperdual<T, 2>>::value), 4ULL);
  TTS_TYPE_IS((std::tuple_element_t<0, flx::hyperdual<T, 2>>), T);

  TTS_CONSTEXPR_EXPECT((flx::concepts::hyperdual<flx::hyperdual<T, 2>>));
  TTS_CONSTEXPR_EXPECT((flx::concepts::hyperdual<eve::wide<flx::hyperdual<T, 2>>>));
  TTS_CONSTEXPR_EXPECT_NOT(flx::concepts::hyperdual<T>);
  TTS_CONSTEXPR_EXPECT(flx::concepts::base<T>);
  TTS_CONSTEXPR_EXPECT(flx::concepts::base<eve::wide<T>>);

  TTS_CONSTEXPR_EQUAL((sizeof(eve::wide<flx::hyperdual<T, 2>>)), 4 * sizeof(eve::wide<T>));
};

TTS_CASE("The guides read an order out of a count of values")
{
  // The second parameter is the order, not the number of components.
  TTS_TYPE_IS((decltype(flx::hyperdual {1.0, 2.0})), (flx::hyperdual<double, 1>));
  TTS_TYPE_IS((decltype(flx::hyperdual {1.0f, 2.0f, 3.0f, 4.0f})), (flx::hyperdual<float, 2>));
  TTS_TYPE_IS((decltype(flx::hyperdual {
                  kumi::tuple {1.0, 2.0, 3.0, 4.0}
  })),
              (flx::hyperdual<double, 2>));
};

TTS_CASE("A constant and a variable differ by what sits in front of the units")
{
  // Bit i of a component index says the component carries unit i.
  flx::hyperdual<double, 2> constant(2.5);

  TTS_EQUAL(get<0>(constant), 2.5);
  TTS_EQUAL(get<1>(constant), 0.0);
  TTS_EQUAL(get<3>(constant), 0.0);

  flx::hyperdual<double, 2> variable(2.5, flx::as_var {});

  TTS_EQUAL(get<0>(variable), 2.5);
  TTS_EQUAL(get<1>(variable), 1.0);
  TTS_EQUAL(get<2>(variable), 1.0);
  TTS_EQUAL(get<3>(variable), 0.0);
};

TTS_CASE("The wide form broadcasts and reads back the same way")
{
  flx::hyperdual<double, 2>            variable(2.5, flx::as_var {});
  eve::wide<flx::hyperdual<double, 2>> broad(variable);

  TTS_EQUAL(get<0>(broad), eve::wide<double> {2.5});
  TTS_EQUAL(get<1>(broad), eve::wide<double> {1.0});
  TTS_EQUAL(get<3>(broad), eve::wide<double> {0.0});
};

TTS_CASE("A hyperdual streams as a sum over its units")
{
  flx::hyperdual<double, 2> variable(2.5, flx::as_var {});
  std::ostringstream        stream;

  stream << variable;

  TTS_EQUAL(stream.str(), std::string {"2.5 + 1e1 + 1e2 + 0e12"});
};
