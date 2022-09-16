//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>

//==================================================================================================
// Tests for eve::acsh
//==================================================================================================
EVE_TEST( "Check behavior of eve::acsh(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(1, +10)
                              )
        )
<typename T>(T const& a0)
{
  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::acsh(vda0))      , eve::acsh(a0));
  TTS_EQUAL(der(eve::acsh(vda0))      , diff(eve::acsh)(a0));
};
