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
TTS_CASE_TPL("Check return types of eve::lpnorm", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::lpnorm)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::lpnorm)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::lpnorm
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::lpnorm(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 5.0)
                          , tts::randoms(-10.0, 10.0)
                          , tts::randoms(-10.0, 10.0)
                           )
              )
<typename T>(T const& rp, T const& a0, T const& a1)
{
  using eve::lpnorm;
  using eve::detail::map;

  auto dlpnorm1 = [&](auto p, auto x, auto y) { auto h = eve::pow_abs(eve::lpnorm(p, x, y), eve::oneminus(p)); return eve::pow_abs(x, eve::dec(p))*h; };
  auto dlpnorm2 = [&](auto p, auto x, auto y) { auto h = eve::pow_abs(eve::lpnorm(p, x, y), eve::oneminus(p)); return eve::pow_abs(y, eve::dec(p))*h; };
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::lpnorm)(rp, a0, a1), map(dlpnorm1, rp, a0, a1), 20.0);
  TTS_ULP_EQUAL(flx::derivative_3rd(eve::lpnorm)(rp, a0, a1), map(dlpnorm2, rp, a0, a1), 20.0);
};
