//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>


//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::pow_abs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::pow_abs)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::pow_abs)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::pow_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::pow_abs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0)
                          , tts::randoms(-10.0, 10.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::pow_abs;
  using eve::detail::map;

  auto dpow_abs1 = [&](auto x, auto y) { return eve::pow_abs(x, eve::dec(y))*y; };
  auto dpow_abs2 = [&](auto x, auto y) { return eve::pow_abs(x, y)*eve::log_abs(x); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::pow_abs)(a0, a1), map(dpow_abs1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::pow_abs)(a0, a1), map(dpow_abs2, a0, a1), 2.0);

};
