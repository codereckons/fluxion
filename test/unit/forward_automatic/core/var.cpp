//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <flx/flx.hpp>

//==================================================================================================
// Tests for flx::var
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::var(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                        ,  tts::randoms(-10, +10)
                        , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, M const& )
{
  using flx::var;

  auto vda0 = var(a0);
  auto vdt  = flx::as_valder_t<T>(a0, eve::one(eve::as(a0)));
  TTS_EQUAL(vda0      , vdt);

  auto vda1 = var(a1, eve::half(eve::as<T>()));
  auto vdt1  = flx::as_valder_t<T>(a1, eve::half(eve::as(a0)));
  TTS_EQUAL(vda1      , vdt1);

  auto vda2 = var(a1, T(1));
  auto vdt2  = flx::as_valder_t<T>(a1, eve::one(eve::as(a0)));
  TTS_EQUAL(vda2      , vdt2);
};
