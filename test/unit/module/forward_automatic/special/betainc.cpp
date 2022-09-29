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
TTS_CASE_WITH( "Check behavior of flx::betainc(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, +1)
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
  using flx::derivative_1st;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::betainc(vda0, a1, a2))      , eve::betainc(a0, a1, a2), 2.0);
  TTS_ULP_EQUAL(der(eve::betainc(vda0, a1, a2))      , derivative_1st(eve::betainc)(a0, a1, a2), 2.0);

};
