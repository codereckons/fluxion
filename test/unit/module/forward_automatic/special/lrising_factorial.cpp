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
// Tests for flx::add
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::lrising_factorial(eve::wide)"
        , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, +10)
                             , tts::randoms(-10, +10)
                             )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_ULP_EQUAL(val(eve::lrising_factorial(vda0, a1))      , eve::lrising_factorial(a0, a1), 2.0);
  TTS_ULP_EQUAL(der(eve::lrising_factorial(vda0, a1))      , derivative_1st(eve::lrising_factorial)(a0, a1), 2.0);
  TTS_ULP_EQUAL(val(eve::lrising_factorial(a0, vda1))      , eve::lrising_factorial(a0, a1), 2.0);
  TTS_ULP_EQUAL(der(eve::lrising_factorial(a0, vda1))      , derivative_2nd(eve::lrising_factorial)(a0, a1), 2.0);
  TTS_ULP_EQUAL(der(eve::lrising_factorial(vda0, vda1))    , eve::sum_of_prod(derivative_2nd(eve::lrising_factorial)(a0, a1), T(1), derivative_1st(eve::lrising_factorial)(a0, a1), T(1)), 4.0);
};
