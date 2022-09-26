/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::ifnot_else
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::ifnot_else(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
             )
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_ULP_EQUAL(val(eve::ifnot_else(a2 > 0, vda0, a1)), eve::if_else(a2 > 0, a1, a0),0.5);
  TTS_ULP_EQUAL(der(eve::ifnot_else(a2 > 0, vda0, a1)), der(eve::if_else(a2 > 0, a1, vda0)),0.5);
  TTS_ULP_EQUAL(val(eve::ifnot_else(a2 > 0, a0, vda1)), eve::if_else(a2 > 0, a1, a0),0.5);
  TTS_ULP_EQUAL(der(eve::ifnot_else(a2 > 0, a0, vda1)), der(eve::if_else(a2 > 0, vda1, a0)),0.5);
};
