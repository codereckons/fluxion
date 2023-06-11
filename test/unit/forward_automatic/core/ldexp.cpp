/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::ldexp
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::ldexp(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                        , tts::randoms(-10, +10)
                        )
        )
  <typename T>(T const& a0, T const& n)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;

  auto vda0 = var(a0);
  auto nn =  eve::trunc(n);
  TTS_ULP_EQUAL(val(eve::ldexp(vda0, nn))      , eve::ldexp(a0, nn), 0.5);
  TTS_ULP_EQUAL(der(eve::ldexp(vda0, nn))      , eve::ldexp(eve::one(eve::as(a0)), nn), 0.5);

};
