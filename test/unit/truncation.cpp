//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation based on generalized hyperdual numbers
  Copyright : FLUXION Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <fluxion/fluxion.hpp>

#include <iostream>
#include <sstream>

// Converting down an order keeps a prefix of the components, and that is not an accident of the
// storage: bit i of a component index says the component carries nilpotent unit i, so the indices
// whose bits all fall under k are exactly the subsets of the first k units. The first four
// components of an order 3 are therefore the order 2 algebra itself, and kumi::extract from index
// zero is the restriction rather than a truncation that happens to land well.
static_assert(!std::is_constructible_v<flx::hyperdual<double, 3>, flx::hyperdual<double, 2>>);
static_assert(std::is_constructible_v<flx::hyperdual<double, 2>, flx::hyperdual<double, 3>>);

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

  // One value per component, so a component read from the wrong index shows itself
  flx::hyperdual<double, 3> full {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  flx::hyperdual<double, 2> half(full);
  check(get<0>(half) == 1.0, "the value survives");
  check(get<1>(half) == 2.0, "unit 0 survives");
  check(get<2>(half) == 3.0, "unit 1 survives");
  check(get<3>(half) == 4.0, "units 0 and 1 survive together");

  flx::hyperdual<double, 1> quarter(full);
  check(get<0>(quarter) == 1.0, "the value survives twice over");
  check(get<1>(quarter) == 2.0, "unit 0 survives twice over");

  // Assigning from a greater order is the same restriction, written the other way
  flx::hyperdual<double, 2> assigned {};
  assigned = full;
  check(get<3>(assigned) == 4.0, "assignment restricts as construction does");

  // What is dropped is exactly what carries unit 2, which is what indices 4 to 7 have in common.
  // The streamed form says it best: the restriction reads as a prefix of what it came from.
  std::ostringstream whole;
  std::ostringstream part;
  whole << full;
  part << half;
  check(whole.str() == "1 + 2e1 + 3e2 + 4e12 + 5e3 + 6e13 + 7e23 + 8e123",
        "the order 3 reads in order");
  check(part.str() == "1 + 2e1 + 3e2 + 4e12", "the order 2 reads as its first half");
  check(whole.str().rfind(part.str(), 0) == 0, "and is a prefix of it, component for component");

  return broken;
}
