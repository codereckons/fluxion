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
// Tests for flx::airy_ai
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::airy_ai(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0.1, 10.0)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::airy_ai(vda0))      , eve::airy_ai(a0));
  TTS_EQUAL(der(eve::airy_ai(vda0))      , derivative(eve::airy_ai)(a0));
};
