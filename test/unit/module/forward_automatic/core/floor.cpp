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
// Tests for flx::floor
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::floor(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
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
  TTS_EQUAL(val(eve::floor(vda0))      , eve::floor(a0));
  TTS_EQUAL(val(eve::floor[mask](vda0)), eve::floor[mask](a0));
  TTS_EQUAL(der(eve::floor(vda0))      , derivative(eve::floor)(a0));
  TTS_EQUAL(der(eve::floor[mask](vda0)), eve::if_else(mask, derivative(eve::floor)(a0), eve::one));
};
