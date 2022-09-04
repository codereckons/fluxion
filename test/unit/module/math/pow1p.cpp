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
TTS_CASE_TPL("Check return types of eve::pow1p", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::pow1p)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::pow1p)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::pow1p
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::pow1p(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0)
                          , tts::randoms(-10.0, 10.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::pow1p;
  using eve::detail::map;

  auto dpow1p1 = [&](auto x, auto y) { return eve::pow1p(x, eve::dec(y))*y; };
  auto dpow1p2 = [&](auto x, auto y) { return eve::pow1p(x, y)*eve::log1p(x); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::pow1p)(a0, a1), map(dpow1p1, a0, a1), 2.0);
  TTS_ULP_EQUAL(flx::diff_2nd(eve::pow1p)(a0, a1), map(dpow1p2, a0, a1), 2.0);

};
