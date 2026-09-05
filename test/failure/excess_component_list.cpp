//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
// build error-gcc: hyperdual<double, 1>::hyperdual
// build error-clang: no matching constructor for initialization of 'flx::hyperdual<double, 1>'

// A list longer than the algebra is refused rather than cut down to size. Truncation is the one
// conversion the type performs, and it only ever happens between two hyperduals, where the order
// says what is dropped. Two components are asked for here, four are given.

#include <fluxion/fluxion.hpp>

int main()
{
  flx::hyperdual<double, 1> h {1.0, 2.0, 3.0, 4.0};
  return static_cast<int>(get<0>(h));
}
