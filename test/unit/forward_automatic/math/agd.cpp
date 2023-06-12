//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::agd
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::agd(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.5, 1.5) )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::agd(vda0))      , eve::agd(a0));
  TTS_EQUAL(der(eve::agd(vda0))      , derivative(eve::agd)(a0));
};
