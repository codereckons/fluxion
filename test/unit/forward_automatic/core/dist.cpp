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
// Tests for flx::dist
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::dist(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  TTS_EQUAL(val(eve::dist(vda0, a1))  , eve::dist(a0, a1));
  TTS_EQUAL(val(eve::dist(a0, vda1))  , eve::dist(a0, a1));
  TTS_EQUAL(der(eve::dist(vda0, a1))  , derivative_1st(eve::dist)(a0, a1));
  TTS_EQUAL(der(eve::dist(a0, vda1))  , derivative_2nd(eve::dist)(a0, a1));
  TTS_ULP_EQUAL(der(eve::dist(vda0, vda1))    , eve::sum_of_prod(derivative_2nd(eve::dist)(a0, a1), T(1), derivative_1st(eve::dist)(a0, a1), T(1)), 0.5);
  TTS_ULP_EQUAL(der(eve::dist(vda0, vda1))    , derivative_2nd(eve::dist)(a0, a1)+ derivative_1st(eve::dist)(a0, a1), 0.5);
  auto vdba0 = flx::as_valder_t<T>(a0, a2);
  auto vdba1 = flx::as_valder_t<T>(a1, a3);
  TTS_ULP_EQUAL(der(eve::dist(vdba0, vdba1))    , eve::sum_of_prod(derivative_2nd(eve::dist)(a0, a1), a3, derivative_1st(eve::dist)(a0, a1), a2), 0.5);
};
