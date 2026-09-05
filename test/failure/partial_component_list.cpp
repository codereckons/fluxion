//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
// build error-gcc: hyperdual<double, 2>::hyperdual
// build error-clang: no matching constructor for initialization of 'flx::hyperdual<double, 2>'

// A list shorter than the algebra is refused rather than completed with zeros. Filling the rest in
// would assert in silence that those derivatives are zero, which is a claim about the function, not
// a convenience. Four components are asked for here, two are given.

#include <fluxion/fluxion.hpp>

int main()
{
  flx::hyperdual<double, 2> h {1.0, 2.0};
  return static_cast<int>(get<0>(h));
}
