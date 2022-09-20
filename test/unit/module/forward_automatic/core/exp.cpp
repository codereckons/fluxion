//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <flx/forward_automatic/forward_automatic.hpp>
#include <flx/flx.hpp>

///==================================================================================================
// Tests for flx::exp
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::exp(eve::valder)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, M const& /*mask*/)
{
  using eve::detail::map;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = flx::var(a0);
  TTS_EQUAL(val(eve::exp(vda0))      , eve::exp(a0));
//  TTS_EQUAL(val(eve::exp[mask](vda0)), eve::exp[mask](a0));
  TTS_EQUAL(der(eve::exp(vda0))      , eve::derivative(eve::exp)(a0));
//  TTS_EQUAL(der(eve::exp[mask](vda0)), eve::if_else(mask, derivative(eve::exp)(a0), eve::one));
};
