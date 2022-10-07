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
// Tests for flx::gegenbauer
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::gegenbauer(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
             )
<typename T>(T const& a1, T const& a2)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_3rd;

  auto vda2 = var(a2);

  TTS_ULP_EQUAL(val(eve::gegenbauer(3.0, a1, vda2))      , eve::gegenbauer(3.0, a1, a2), 0.5);
  TTS_ULP_EQUAL(der(eve::gegenbauer(3.0, a1, vda2))      , derivative_3rd(eve::gegenbauer)(3.0, a1, a2), 0.5);
};
