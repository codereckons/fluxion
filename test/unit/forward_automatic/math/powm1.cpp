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
// Tests for flx::add
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::powm1(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, +10)
                              , tts::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_ULP_EQUAL(val(eve::powm1(vda0, a1))      , eve::powm1(a0, a1), 0.5);
  TTS_ULP_EQUAL(der(eve::powm1(vda0, a1))      , derivative_1st(eve::powm1)(a0, a1), 10.0);
  TTS_ULP_EQUAL(val(eve::powm1(a0, vda1))      , eve::powm1(a0, a1), 0.5);
  TTS_ULP_EQUAL(der(eve::powm1(a0, vda1))      , derivative_2nd(eve::powm1)(a0, a1), 10.0);
};
