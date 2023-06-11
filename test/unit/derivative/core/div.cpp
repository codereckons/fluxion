//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::div", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::div)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::div)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::div
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::div(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                          , tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::div;
  using eve::detail::map;

  auto ddiv1=[&](auto , auto f) {return  1/f; };
  auto ddiv2=[&](auto e, auto f) {return -e/eve::sqr(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::div)(a0, a1), map(ddiv1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::div)(a0, a1), map(ddiv2, a0, a1), 0.5);
};
