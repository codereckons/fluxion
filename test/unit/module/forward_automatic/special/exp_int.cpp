//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/special.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::exp_int
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::exp_int(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, 2)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::exp_int(3, vda0))      , eve::exp_int(3, a0));
  TTS_EQUAL(der(eve::exp_int(3, vda0))      , derivative_2nd(eve::exp_int)(3, a0));
};
