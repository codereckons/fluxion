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
// Tests for flx::nthroot
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::nthroot(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, +10)
                        , tts::ramp(1, 1)
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
  TTS_ULP_EQUAL(val(eve::nthroot(vda0, a1))  , eve::nthroot(a0, a1), 0.5);
  TTS_ULP_EQUAL(der(eve::nthroot(vda0, a1))  , derivative_1st(eve::nthroot)(a0, a1), 0.5);
};
