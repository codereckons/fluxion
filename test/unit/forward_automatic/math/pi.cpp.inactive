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
// Tests for flx::pi
//==================================================================================================
TTS_CASE_WITH( "Check behavior of pi(valder)"
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
  TTS_EQUAL(val(eve::pi(eve::as(vda0))), eve::pi(eve::as(a0)));
  TTS_EQUAL(der(eve::pi(eve::as(vda0))), eve::zero(eve::as(a0)));
};
