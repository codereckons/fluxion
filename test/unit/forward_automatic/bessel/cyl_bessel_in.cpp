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
// Tests for flx::cyl_bessel_in
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::cyl_bessel_in(eve::wide)"
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

  auto vda0 = var(a0);
  std::cout << eve::cyl_bessel_in(3, a0) << std::endl;
  std::cout <<  derivative_2nd(eve::cyl_bessel_in)(3, a0)<< std::endl;
  TTS_EQUAL(val(eve::cyl_bessel_in(3, vda0))      , eve::cyl_bessel_in(3, a0));
  TTS_EQUAL(der(eve::cyl_bessel_in(3, vda0))      , derivative_2nd(eve::cyl_bessel_in)(3, a0));
};
