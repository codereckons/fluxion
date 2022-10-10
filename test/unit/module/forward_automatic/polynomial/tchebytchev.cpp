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
// Tests for flx::tchebytchev
//==================================================================================================
TTS_CASE_WITH( "Check behavior of flx::tchebytchev(eve::wide)"
             , flx::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1, +1)
                             , tts::as_integer(tts::ramp(1))
                             )
             )
  <typename T, typename N>(T const& a1, N const & n)
{
  using flx::var;
  using flx::val;
  using flx::der;
  using flx::derivative_2nd;

  auto vda1 = var(a1);

   TTS_ULP_EQUAL(val(eve::tchebytchev(n, vda1))      , eve::tchebytchev(n, a1), 0.5);
   TTS_ULP_EQUAL(der(eve::tchebytchev(n, vda1))      , derivative_2nd(eve::tchebytchev)(n, a1), 0.5);
   TTS_ULP_EQUAL(val(eve::kind_2(eve::tchebytchev)(n, vda1))      , eve::kind_2(eve::tchebytchev)(n, a1), 0.5);
   TTS_ULP_EQUAL(der(eve::kind_2(eve::tchebytchev)(n, vda1))      , eve::tchebytchev(eve::decorated<flx::derivative_<2>(eve::kind_2_type)>(), n, a1), 0.5);
};
