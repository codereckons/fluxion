//======================================================================================================================
/*
  FLUXION - Post-Modern Automatic Derivation
  Copyright : FLUXION Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/helpers.hpp>

namespace flx
{
  //! @brief EVE vocabulary spoken as fluxion's own
  //!
  //! nodes and coefficients name the operands of polynomial evaluation. fluxion reuses EVE's rather
  //! than defining its own.
  using eve::coefficients;
  using eve::nodes;
}
