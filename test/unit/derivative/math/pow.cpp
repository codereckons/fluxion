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
TTS_CASE_TPL("Check return types of eve::pow", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::pow)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::pow)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::pow
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::pow(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0)
                          , tts::randoms(-10.0, 10.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::pow;
  using eve::detail::map;

  auto dpow1 = [&](auto x, auto y) { return eve::pow(x, eve::dec(y))*y; };
  auto dpow2 = [&](auto x, auto y) { return eve::pow(x, y)*eve::log(x); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::pow)(a0, a1), map(dpow1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::pow)(a0, a1), map(dpow2, a0, a1), 2.0);

};
