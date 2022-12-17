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
// Tests for flx::maxmag
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::maxmag(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& /*maaask*/)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_1st;
  using flx::derivative_2nd;
  using flx::derivative_3rd;

  auto vda0 = var(a0);
  auto vda1 = var(a1);
  auto vda2 = var(a2);
  TTS_EQUAL(val(eve::maxmag(vda0, a1, a2))  , eve::maxmag(a0, a1, a2));
  TTS_EQUAL(val(eve::maxmag(a0, vda1, a2))  , eve::maxmag(a0, a1, a2));
  TTS_EQUAL(val(eve::maxmag(a0, a1, vda2))  , eve::maxmag(a0, a1, a2));
  TTS_EQUAL(der(eve::maxmag(vda0, a1, a2))  , derivative_1st(eve::maxmag)(a0, a1, a2));
  TTS_EQUAL(der(eve::maxmag(a0, vda1, a2))  , derivative_2nd(eve::maxmag)(a0, a1, a2));
  TTS_EQUAL(der(eve::maxmag(a0, a1, vda2))  , derivative_3rd(eve::maxmag)(a0, a1, a2));

//   TTS_EQUAL(val(eve::maxmag[mask](vda0, a1, a2))  , eve::maxmag[ mask ](a0, a1, a2)); 
//   TTS_EQUAL(val(eve::maxmag[mask](a0, vda1, a2))  , eve::maxmag[ mask ](a0, a1, a2)); 
//   TTS_EQUAL(val(eve::maxmag[mask](a0, a1, vda2))  , eve::maxmag[ mask ](a0, a1, a2)); 
//   TTS_EQUAL(der(eve::maxmag[mask](vda0, a1, a2))  , eve::if_else( mask , derivative_1st(eve::maxmag)(a0, a1, a2), eve::one)); 
//   TTS_EQUAL(der(eve::maxmag[mask](a0, vda1, a2))  , eve::if_else( mask , derivative_2nd(eve::maxmag)(a0, a1, a2), eve::zero)); 
//   TTS_EQUAL(der(eve::maxmag[mask](a0, a1, vda2))  , eve::if_else( mask , derivative_3rd(eve::maxmag)(a0, a1, a2), eve::zero)); 
};
