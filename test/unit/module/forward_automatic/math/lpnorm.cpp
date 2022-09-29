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
// Tests for flx::lpnorm
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::lpnorm(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(2, 5)
                             , tts::randoms(1, +10)
                             , tts::randoms(1, +10)
                             , tts::randoms(1, +10)
                             , tts::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& p,  T const& a0, T const& a1, T const& a2, M const & mask)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;
  using flx::derivative_3rd;
  using flx::derivative_nth;

  auto vdp = var(p);
  auto vda0 = var(a0);
  auto vda1 = var(a1);
  auto vda2 = var(a2);
  TTS_EQUAL(val(eve::lpnorm(vdp, a0, a1, a2))      , eve::lpnorm(p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm(vdp, a0, a1, a2))      , derivative_1st(eve::lpnorm)(p, a0, a1, a2));
  TTS_EQUAL(val(eve::lpnorm(p, vda0, a1, a2))      , eve::lpnorm(p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm(p, vda0, a1, a2))      , derivative_2nd(eve::lpnorm)(p, a0, a1, a2));
  TTS_EQUAL(val(eve::lpnorm(p, a0, vda1, a2))      , eve::lpnorm(p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm(p, a0, vda1, a2))      , derivative_3rd(eve::lpnorm)(p, a0, a1, a2));
  TTS_EQUAL(val(eve::lpnorm(p, a0, a1, vda2))      , eve::lpnorm(p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm(p, a0, a1, vda2))      , derivative_nth<4>(eve::lpnorm)(p, a0, a1, a2));

  TTS_EQUAL(val(eve::lpnorm[mask](vdp, a0, a1, a2)), eve::lpnorm[mask](p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm[mask](vdp, a0, a1, a2)), eve::if_else(mask,derivative_1st(eve::lpnorm)(p, a0, a1, a2), eve::one));
  TTS_EQUAL(val(eve::lpnorm[mask](p, vda0, a1, a2)), eve::lpnorm[mask](p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm[mask](p, vda0, a1, a2)), eve::if_else(mask, derivative_2nd(eve::lpnorm)(p, a0, a1, a2), eve::zero));
  TTS_EQUAL(val(eve::lpnorm[mask](p, a0, vda1, a2)), eve::lpnorm[mask](p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm[mask](p, a0, vda1, a2)), eve::if_else(mask, derivative_3rd(eve::lpnorm)(p, a0, a1, a2), eve::zero));
  TTS_EQUAL(val(eve::lpnorm[mask](p, a0, a1, vda2)), eve::lpnorm[mask](p, a0, a1, a2));
  TTS_EQUAL(der(eve::lpnorm[mask](p, a0, a1, vda2)), eve::if_else(mask, derivative_nth<4>(eve::lpnorm)(p, a0, a1, a2), eve::zero));


};
