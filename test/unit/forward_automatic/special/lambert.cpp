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
// Tests for flx::frac
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::lambert(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-0.5, +10)
                              )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  auto [f, t] = eve::lambert(vda0);
  auto [fv, tv]= eve::lambert(a0);
  auto [fd, td]= flx::derivative(eve::lambert)(a0);

  TTS_ULP_EQUAL(val(f)      , fv, 0.5);
  TTS_ULP_EQUAL(val(t)      , tv, 0.5);
  TTS_ULP_EQUAL(der(f)      , fd, 0.5);
  TTS_ULP_EQUAL(der(t)      , td, 0.5);
};
