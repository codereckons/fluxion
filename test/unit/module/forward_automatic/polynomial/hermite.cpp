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
// Tests for flx::hermite
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::hermite(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             )
             )
<typename T>(T const& a1)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_2nd;

  auto vda1 = var(a1);

  TTS_ULP_EQUAL(val(eve::hermite(T(3), vda1))      , eve::hermite(3, a1), 0.5);
  TTS_ULP_EQUAL(der(eve::hermite(T(3), vda1))      , derivative_2nd(eve::hermite)(3, a1), 0.5);
};
