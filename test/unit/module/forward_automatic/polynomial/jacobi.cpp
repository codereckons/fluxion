//==================================================================================================
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
// Tests for flx::jacobi
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::jacobi(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_4th;

  auto vda2 = var(a2);

  TTS_ULP_EQUAL(val(eve::jacobi(T(3), a0, a1, vda2))      , eve::jacobi(3, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(der(eve::jacobi(T(3), a0, a1, vda2))      , derivative_4th(eve::jacobi)(3, a0, a1, a2), 0.5);
};
