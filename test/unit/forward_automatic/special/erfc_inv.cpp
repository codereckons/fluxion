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
// Tests for flx::erfc
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::erfc_inv(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, 2)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::erfc_inv(vda0))      , eve::erfc_inv(a0));
  TTS_EQUAL(der(eve::erfc_inv(vda0))      , derivative(eve::erfc_inv)(a0));
};
