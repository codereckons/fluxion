//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::geommean", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::geommean)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::geommean)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::geommean
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::geommean(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(-10.0,10.0)
                           , tts::randoms(-10.0,10.0)
                           , tts::randoms(-10.0,10.0)
                           )
              )
<typename T>(T const& a0, T const & a1, T const & a2)
{
  using eve::geommean;
  using eve::detail::map;

  auto dgeommean1 = [&](auto e, auto f) { return flx::derivative(eve::sqrt)(e*f)*f; };
  auto dgeommean2 = [&](auto e, auto f) { return flx::derivative(eve::sqrt)(e*f)*e; };
  auto dgeommean3 = [&](auto e, auto f, auto g ){ return flx::derivative(eve::cbrt)(e*f*g)*e*f; };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::geommean)(a0, a1), map(dgeommean1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::geommean)(a0, a1), map(dgeommean2, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_3rd(eve::geommean)(a0, a1, a2), map(dgeommean3, a0, a1, a2), 10.0);

};
