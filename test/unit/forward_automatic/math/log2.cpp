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
// Tests for flx::log2
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::log2(eve::wide)"
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
  TTS_EQUAL(val(eve::log2(vda0))      , eve::log2(a0));
  TTS_EQUAL(der(eve::log2(vda0))      , derivative(eve::log2)(a0));
};
