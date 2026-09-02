//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

#include <iostream>

int main()
{
  std::cout << "fluxion " << fluxion::version << "\n";

  return fluxion::version[ 0 ] == '\0' ? 1 : 0;
}
