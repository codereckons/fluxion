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
// Tests for flx::nearest
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::nearest(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& /*maaask*/)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::nearest(vda0))      , eve::nearest(a0));
//   TTS_EQUAL(val(eve::nearest[mask](vda0)), eve::nearest[ mask ](a0)); 
  TTS_EQUAL(der(eve::nearest(vda0))      , derivative(eve::nearest)(a0));
//   TTS_EQUAL(der(eve::nearest[mask](vda0)), eve::if_else( mask , derivative(eve::nearest)(a0), eve::one)); 
};
