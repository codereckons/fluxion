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
// Tests for flx::hypot
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::hypot(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              )
        )
  <typename T>(T const& a0, T const& a1, T const&  )
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
//   using flx::derivative_2nd;
//   using flx::derivative_3rd;

  auto vda0 = var(a0);
//   auto vda1 = var(a1);
//   auto vda2 = var(a2);
  TTS_IEEE_EQUAL(val(eve::hypot(vda0, a1    ))      , eve::hypot(a0, a1));
//   TTS_IEEE_EQUAL(val(eve::hypot(vda0, a1, a2))      , eve::hypot(a0, a1, a2));
//   TTS_IEEE_EQUAL(der(eve::hypot(vda0, a1, a2))      , derivative_1st(eve::hypot)(a0, a1, a2));
//   TTS_IEEE_EQUAL(val(eve::hypot(a0, vda1, a2))      , eve::hypot(a0, a1, a2));
//   TTS_IEEE_EQUAL(der(eve::hypot(a0, vda1, a2))      , derivative_2nd(eve::hypot)(a0, a1, a2));
//   TTS_IEEE_EQUAL(val(eve::hypot(a0, a1, vda2))      , eve::hypot(a0, a1, a2));
//   TTS_IEEE_EQUAL(der(eve::hypot(a0, a1, vda2))      , derivative_3rd(eve::hypot)(a0, a1, a2));

};
