//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::tchebytchev
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::tchebytchev(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1, +1))
             )
  <typename T>(T const& a1)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_2nd;

  auto vda1 = var(a1);

  for(int n=1; n < 4; ++n)
  {
    TTS_ULP_EQUAL(val(eve::tchebytchev(n, vda1))             , eve::tchebytchev(n, a1), 0.5);
    TTS_ULP_EQUAL(der(eve::tchebytchev(n, vda1))             , flx::derivative_2nd(eve::tchebytchev)(n, a1), 0.5);
  }
};
