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
// Tests for flx::clamp
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::clamp(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(0, +10)
                              , tts::randoms(0, +10)
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
  auto lo =  a1;
  auto hi =  a1+a2;
  auto vda0 = var(a0);
  auto vdlo = var(lo);
  auto vdhi = var(hi);
  TTS_EQUAL(val(eve::clamp(vda0, lo, hi))      , eve::clamp(a0, lo, hi));
  TTS_EQUAL(der(eve::clamp(vda0, lo, hi))      , derivative_1st(eve::clamp)(a0, lo, hi));
  TTS_EQUAL(val(eve::clamp(a0, vdlo, hi))      , eve::clamp(a0, lo, hi));
  TTS_EQUAL(der(eve::clamp(a0, vdlo, hi))      , derivative_2nd(eve::clamp)(a0, lo, hi));
  TTS_EQUAL(val(eve::clamp(a0, lo, vdhi))      , eve::clamp(a0, lo, hi));
  TTS_EQUAL(der(eve::clamp(a0, lo, vdhi))      , derivative_3rd(eve::clamp)(a0, lo, hi));
};
