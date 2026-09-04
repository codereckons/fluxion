//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iostream>

#include <fluxion/fluxion.hpp>

int main()
{
  auto x = flx::variable<2>(2.5);

  std::cout << "fluxion " << fluxion::version << "\n";
  std::cout << "x           = " << x << "\n";
  std::cout << "at order 1  = " << flx::restrict_to<1>(x) << "\n";

  return 0;
}
