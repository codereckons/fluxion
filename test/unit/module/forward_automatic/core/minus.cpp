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
// Tests for flx::minus
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::minus(eve::wide)"
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
  TTS_EQUAL(val(eve::minus(vda0))      , eve::minus(a0));
  TTS_EQUAL(val(eve::minus[mask](vda0)), eve::minus[mask](a0));
  TTS_EQUAL(der(eve::minus(vda0))      , derivative(eve::minus)(a0));
  TTS_EQUAL(der(eve::minus[mask](vda0)), eve::if_else(mask, derivative(eve::minus)(a0), eve::one));
};
