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
// Tests for flx::cyl_bessel_kn
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::cyl_bessel_kn(eve::wide)"
        , flx::test::simd::ieee_reals
        , tts::generate ( tts::randoms(0.1, 10.0)
                        , tts::as_integer(tts::ramp(0))
                              )
        )
<typename T, typename N>(T const& a0, N const & )
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_2nd;
  auto n = 3;
  auto vda0 = var(a0);
  TTS_ULP_EQUAL(val(eve::cyl_bessel_kn(n, vda0))      , eve::cyl_bessel_kn(n, a0), 1.0);
  TTS_ULP_EQUAL(der(eve::cyl_bessel_kn(n, vda0))      , derivative_2nd(eve::cyl_bessel_kn)(n, a0), 1.0);
};
