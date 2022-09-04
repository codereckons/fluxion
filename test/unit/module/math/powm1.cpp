//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/differential/math.hpp>


//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::powm1", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::powm1)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::powm1)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::powm1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::powm1(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0)
                          , tts::randoms(-10.0, 10.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::powm1;
  using eve::detail::map;

  auto dpowm11 = [&](auto x, auto y) { return eve::pow(x, eve::dec(y))*y; };
  auto dpowm12 = [&](auto x, auto y) { return eve::pow(x, y)*eve::log(x); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::powm1)(a0, a1), map(dpowm11, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::diff_2nd(eve::powm1)(a0, a1), map(dpowm12, a0, a1), 2.0);

};
