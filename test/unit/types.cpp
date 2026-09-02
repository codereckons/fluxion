//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

#include <iostream>

// The types exist, carry the right shape, and eve::wide falls out of the tuple protocol. Everything
// a static_assert can say is said here; what needs to run is checked in main below.
template<typename T> void shape()
{
  static_assert(flx::hyperdual<T, 1>::static_dimension == 2);
  static_assert(flx::hyperdual<T, 2>::static_dimension == 4);
  static_assert(flx::hyperdual<T, 3>::static_dimension == 8);
  static_assert(flx::hyperdual<T, 4>::static_dimension == 16);

  static_assert(std::tuple_size<flx::hyperdual<T, 2>>::value == 4);
  static_assert(std::same_as<std::tuple_element_t<0, flx::hyperdual<T, 2>>, T>);

  static_assert(flx::concepts::hyperdual<flx::hyperdual<T, 2>>);
  static_assert(flx::concepts::hyperdual<eve::wide<flx::hyperdual<T, 2>>>);
  static_assert(!flx::concepts::hyperdual<T>);
  static_assert(flx::concepts::base<T>);
  static_assert(flx::concepts::base<eve::wide<T>>);

  static_assert(sizeof(eve::wide<flx::hyperdual<T, 2>>) == 4 * sizeof(eve::wide<T>));
}

template void shape<float>();
template void shape<double>();

int           main()
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

  // Reading goes through get<I>: the named accessors e0, e1, e12 belong to the functions layer,
  // which lands in a later step. Index layout: bit i set means the component carries unit i.
  flx::hyperdual<double, 2> constant(2.5);
  check(get<0>(constant) == 2.5, "value of a constant");
  check(get<1>(constant) == 0.0, "unit-1 part of a constant");
  check(get<3>(constant) == 0.0, "cross part of a constant");

  // A variable seeds a one in front of each nilpotent unit, and nowhere else
  flx::hyperdual<double, 2> variable(2.5, flx::as_var{});
  check(get<0>(variable) == 2.5, "value of a variable");
  check(get<1>(variable) == 1.0, "unit-1 part of a variable");
  check(get<2>(variable) == 1.0, "unit-2 part of a variable");
  check(get<3>(variable) == 0.0, "cross part of a variable");

  // The wide form broadcasts and reads back the same way
  eve::wide<flx::hyperdual<double, 2>> broad(variable);
  check(eve::all(get<0>(broad) == 2.5), "value of a broadcast wide");
  check(eve::all(get<1>(broad) == 1.0), "unit-1 part of a broadcast wide");
  check(eve::all(get<3>(broad) == 0.0), "cross part of a broadcast wide");

  return broken;
}
