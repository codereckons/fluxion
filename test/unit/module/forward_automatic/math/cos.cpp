//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for eve::cos
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::cos(eve::wide)"
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
  TTS_ULP_EQUAL(val(eve::cos(vda0))      , eve::cos(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::cos(vda0))      , derivative(eve::cos)(a0), 0.5);
};
