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
// Tests for flx::modf
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::modf(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;

  auto vda0 = var(a0);
  auto [f, t] = eve::modf(vda0);

  TTS_ULP_EQUAL(val(f)      , eve::frac(a0), 0.5);
  TTS_ULP_EQUAL(val(t)      , eve::trunc(a0), 0.5);
  TTS_ULP_EQUAL(der(f)      , eve::one(eve::as(a0)), 0.5);
  TTS_ULP_EQUAL(der(t)      , eve::zero(eve::as(a0)), 0.5);
};
