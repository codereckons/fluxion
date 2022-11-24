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
// Tests for flx::log10
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::log10(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, +100)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::log10(vda0))      , eve::log10(a0));
  TTS_EQUAL(der(eve::log10(vda0))      , derivative(eve::log10)(a0));
};
