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
// Tests for flx::div
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::div(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& mask)
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
  TTS_ULP_EQUAL(val(eve::div(vda0, a1    ))      , eve::div(a0, a1    ), 1.0);
  TTS_ULP_EQUAL(der(eve::div(vda0, a1    ))      , derivative_1st(eve::div)(a0, a1    ), 1.0);
  TTS_ULP_EQUAL(val(eve::div(a0, vda1    ))      , eve::div(a0, a1    ), 1.0);
  TTS_ULP_EQUAL(der(eve::div(a0, vda1    ))      , derivative_2nd(eve::div)(a0, a1    ), 1.0);
  TTS_ULP_EQUAL(val(eve::div(vda0, vda1  ))      , eve::div(a0, a1    ), 1.0);
  TTS_ULP_EQUAL(der(eve::div(vda0, vda1  ))      , derivative_1st(eve::div)(a0, a1    )+derivative_2nd(eve::div)(a0, a1    ), 1.0);

  TTS_ULP_EQUAL(val(eve::div(vda0, a1, a2))      , eve::div(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(der(eve::div(vda0, a1, a2))      , derivative_1st(eve::div)(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(der(eve::div(a0, vda1, a2))      , derivative_2nd(eve::div)(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(val(eve::div(a0, vda1, a2))      , eve::div(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(der(eve::div(a0, vda1, a2))      , derivative_2nd(eve::div)(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(val(eve::div(a0, a1, vda2))      , eve::div(a0, a1, a2), 1.0);
  TTS_ULP_EQUAL(der(eve::div(a0, a1, vda2))      , derivative_3rd(eve::div)(a0, a1, a2), 1.0);

  TTS_ULP_EQUAL(val(eve::div[mask](vda0, a1)), eve::div[mask](a0, a1), 1.0);
//   TTS_ULP_EQUAL(val(eve::div[mask](vda0, a1, a2)), eve::div[mask](a0, a1, a2), 1.0);
//   TTS_ULP_EQUAL(der(eve::div[mask](vda0, a1, a2)), eve::if_else(mask, derivative_1st(eve::div)(a0, a1, a2), eve::one), 1.0);
//   TTS_ULP_EQUAL(val(eve::div[mask](a0, vda1, a2)), eve::div[mask](a0, a1, a2), 1.0);
//   TTS_ULP_EQUAL(der(eve::div[mask](a0, vda1, a2)), eve::if_else(mask, derivative_2nd(eve::div)(a0, a1, a2), eve::zero), 1.0);
//   TTS_ULP_EQUAL(val(eve::div[mask](a0, a1, vda2)), eve::div[mask](a0, a1, a2), 1.0);
//   TTS_ULP_EQUAL(der(eve::div[mask](a0, a1, vda2)), eve::if_else(mask, derivative_3rd(eve::div)(a0, a1, a2), eve::zero), 1.0);

//   der(vda2) = T(0.5);
//   TTS_ULP_EQUAL(der(eve::div(a0, vda1, vda2))      , derivative_2nd(eve::div)(a0, a1, a2)+der(vda2)*derivative_3rd(eve::div)(a0, a1, a2), 1.0);

};
