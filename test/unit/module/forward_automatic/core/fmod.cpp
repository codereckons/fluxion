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
// Tests for flx::fmod
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::fmod(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, T const& a1 )
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::fmod(vda0, a1))      , eve::fmod(a0, a1));
  TTS_EQUAL(der(eve::fmod(vda0, a1))      , derivative_1st(eve::fmod)(a0, a1));
  TTS_EQUAL(val(eve::fmod(a0, vda1))      , eve::fmod(a0, a1));
  TTS_EQUAL(der(eve::fmod(a0, vda1))      , derivative_2nd(eve::fmod)(a0, a1));
};
