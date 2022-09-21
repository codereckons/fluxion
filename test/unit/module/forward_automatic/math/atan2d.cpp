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
TTS_CASE_WITH( "Check behavior of flx::atan2d(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
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
  TTS_ULP_EQUAL(val(eve::atan2d(vda0, a1))      , eve::atan2d(a0, a1), 2.0);
  TTS_ULP_EQUAL(der(eve::atan2d(vda0, a1))      , derivative_1st(eve::atan2d)(a0, a1), 2.0);
  TTS_ULP_EQUAL(val(eve::atan2d(a0, vda1))      , eve::atan2d(a0, a1), 2.0);
  TTS_ULP_EQUAL(der(eve::atan2d(a0, vda1))      , derivative_2nd(eve::atan2d)(a0, a1), 2.0);
};
