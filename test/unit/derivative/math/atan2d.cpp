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
TTS_CASE_TPL("Check return types of eve::atan2d", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::atan2d)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::atan2d)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::atan2d
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::atan2d(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                          , tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::atan2d;
  using eve::detail::map;

  auto datan2d1 = [&](auto x, auto y) { return eve::radindeg(eve::rec(eve::sqr(x)+eve::sqr(y))*y); };
  auto datan2d2 = [&](auto x, auto y) { return eve::radindeg(eve::rec(eve::sqr(x)+eve::sqr(y))*x); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::atan2d)(a0, a1), map(datan2d1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::atan2d)(a0, a1), map(datan2d2, a0, a1), 2.0);
};
