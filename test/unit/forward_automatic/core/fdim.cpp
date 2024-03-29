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
// Tests for flx::fdim
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::fdim(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const&  )
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::fdim(vda0, a1))  , eve::fdim(a0, a1));
  TTS_EQUAL(val(eve::fdim(a0, vda1))  , eve::fdim(a0, a1));
  TTS_EQUAL(der(eve::fdim(vda0, a1))  , derivative_1st(eve::fdim)(a0, a1));
  TTS_EQUAL(der(eve::fdim(a0, vda1))  , derivative_2nd(eve::fdim)(a0, a1));


//   TTS_EQUAL(val(eve::fdim[mask](vda0, a1))  , eve::fdim[mask](a0, a1));
//   TTS_EQUAL(val(eve::fdim[mask](a0, vda1))  , eve::fdim[mask](a0, a1));
//   TTS_EQUAL(der(eve::fdim[mask](vda0, a1))  , eve::if_else(mask, derivative_1st(eve::fdim)(a0, a1), eve::one));
//   TTS_EQUAL(der(eve::fdim[mask](a0, vda1))  , eve::if_else(mask, derivative_2nd(eve::fdim)(a0, a1), eve::zero));
};
