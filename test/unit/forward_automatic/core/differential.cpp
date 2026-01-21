//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <flx/flx.hpp>
#include <eve/wide.hpp>
#include <iostream>

//==================================================================================================
// Tests for flx::differential
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::differential"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        ,  tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
<typename T>(T const& a0, T const& a1, T const& a2
                        , T const& da0,  T const& da1, T const& da2)
{
  auto f = [](auto x, auto y,  auto z){return eve::fma(x, y, z); };
  auto df = [](auto x, auto y,  auto
             ,  auto dx, auto dy,  auto dz){
    return y*dx+x*dy+dz;
  };

  auto d = flx::differential(f, a0, a1, a2);
  auto dif = d(da0, da1, da2);
  auto ref  = df(a0, a1, a2, da0, da1, da2);
  TTS_EQUAL(dif      , ref);
  TTS_EQUAL(d(1.0, 1.0, 1.0), df(a0, a1, a2, 1.0, 1.0, 1.0));
  TTS_EQUAL(d(da0, 1.0, 1.0), df(a0, a1, a2, da0, 1.0, 1.0));

};
