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
// Tests for flx::asecpi
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::asecpi(eve::wide)"
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
  TTS_EQUAL(val(eve::asecpi(vda0))      , eve::asecpi(a0));
  TTS_EQUAL(der(eve::asecpi(vda0))      , derivative(eve::asecpi)(a0));
};
