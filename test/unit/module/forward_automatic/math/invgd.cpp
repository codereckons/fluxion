//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <flx/flx.hpp>

// auto maxi = []<typename T>(eve::as<T> const & tgt)
// {
//   return eve::pio_2(tgt);
// };
// auto mini = []<typename T>(eve::as<T> const & tgt)
// {
//   return -eve::pio_2(tgt);
// };
//==================================================================================================
// Tests for flx::invgd
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::invgd(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.5, 1.5)//mini, maxi)
                              )
        )
<typename T>(T const& a0)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::invgd(vda0))      , eve::invgd(a0));
  TTS_EQUAL(der(eve::invgd(vda0))      , derivative(eve::invgd)(a0));
};
