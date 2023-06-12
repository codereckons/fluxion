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
// Tests for flx::expm1
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::expm1(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::expm1(vda0))      , eve::expm1(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::expm1(vda0))      , derivative(eve::expm1)(a0), 0.5);
};
