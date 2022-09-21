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
// Tests for flx::acosh
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::acosh(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(1, +10)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::acosh(vda0))      , eve::acosh(a0));
  TTS_EQUAL(der(eve::acosh(vda0))      , derivative(eve::acosh)(a0));
};
