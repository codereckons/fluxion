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
// Tests for flx::sub
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::sub(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;

  {
    auto vda0 = var(a0);
    auto vda0r= var(a0);
    auto vda1 = var(a1);
    auto vda1r= var(a1);
    vda0 *= a1;
    vda1 *= vda0r;
    TTS_EQUAL(val(vda0)      , eve::mul(a0, a1));
    TTS_EQUAL(der(vda0)      , der(eve::mul(vda0r, a1)));
    TTS_EQUAL(val(vda1)      , eve::mul(a0, a1));
    TTS_EQUAL(der(vda1)      , der(eve::mul(vda0r, vda1r)));
  }

  {
    auto vda0 = var(a0);
    auto vda1 = var(a1);
    auto vda2 = vda0*a1;
    auto vda3 = vda0*vda1;
    auto vda4 = a0*vda1;

    TTS_EQUAL(val(vda2)      , eve::mul(a0, a1));
    TTS_EQUAL(der(vda2)      , der(eve::mul(vda0, a1)));
    TTS_EQUAL(val(vda3)      , eve::mul(a0, a1));
    TTS_EQUAL(der(vda3)      , der(eve::mul(vda0, vda1)));
    TTS_EQUAL(der(vda4)      , der(eve::mul(a0, vda1)));
  }
};
