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
// Tests for flx::acos
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::acos(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-1, +1)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::acos(vda0))      , eve::acos(a0));
  TTS_EQUAL(der(eve::acos(vda0))      , derivative(eve::acos)(a0));
};
