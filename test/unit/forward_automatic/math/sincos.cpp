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

//==================================================================================================
// Tests for flx::frac
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::sincos(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  auto [f, t] = eve::sincos(vda0);

  TTS_ULP_EQUAL(val(f)      , eve::sin(a0), 0.5);
  TTS_ULP_EQUAL(val(t)      , eve::cos(a0), 0.5);
  TTS_ULP_EQUAL(der(f)      , derivative(eve::sin)(a0), 0.5);
  TTS_ULP_EQUAL(der(t)      , derivative(eve::cos)(a0), 0.5);
};
