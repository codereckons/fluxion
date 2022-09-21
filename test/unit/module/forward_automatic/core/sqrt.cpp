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
// Tests for flx::sqrt
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::sqrt(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, +10)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::sqrt(vda0))      , eve::sqrt(a0), 0.5);
  TTS_ULP_EQUAL(val(eve::sqrt[mask](vda0)), eve::sqrt[mask](a0), 0.5);
  TTS_ULP_EQUAL(der(eve::sqrt(vda0))      , derivative(eve::sqrt)(a0), 0.5);
  TTS_ULP_EQUAL(der(eve::sqrt[mask](vda0)), eve::if_else(mask, derivative(eve::sqrt)(a0), eve::one), 0.5);
};
