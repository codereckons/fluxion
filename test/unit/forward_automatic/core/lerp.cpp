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
// Tests for flx::lerp
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::lerp(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(0, 1)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;
  using flx::derivative_3rd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  auto vda2 = var(a2);
  TTS_EQUAL(val(eve::lerp(vda0, a1, a2))      , eve::lerp(a0, a1, a2));
  TTS_EQUAL(der(eve::lerp(vda0, a1, a2))      , derivative_1st(eve::lerp)(a0, a1, a2));
  TTS_EQUAL(val(eve::lerp(a0, vda1, a2))      , eve::lerp(a0, a1, a2));
  TTS_EQUAL(der(eve::lerp(a0, vda1, a2))      , derivative_2nd(eve::lerp)(a0, a1, a2));
  TTS_EQUAL(val(eve::lerp(a0, a1, vda2))      , eve::lerp(a0, a1, a2));
  TTS_EQUAL(der(eve::lerp(a0, a1, vda2))      , derivative_3rd(eve::lerp)(a0, a1, a2));
};
