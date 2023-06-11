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
// Tests for flx::exponent
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::exponent(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0, +10))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using flx::var;
  using flx::val;
  using flx::der;

  auto vda0 = var(a0);
  auto v = eve::convert(eve::exponent(a0), eve::as<eve::element_type_t<T>>());

  TTS_ULP_EQUAL(val(eve::exponent(vda0)), v, 0.5);
  TTS_ULP_EQUAL(der(eve::exponent(vda0)), eve::zero(eve::as(val(a0))), 0.5);
};
