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
// Tests for flx::cosh
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::cosh(eve::wide)"
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
  TTS_ULP_EQUAL(val(eve::cosh(vda0))      , eve::cosh(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::cosh(vda0))      , derivative(eve::cosh)(a0), 0.5);
};
