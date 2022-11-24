//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::binarize", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::binarize)(eve::as_logical<T>(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::binarize)(eve::as_logical<v_t>(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::binarize
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::binarize(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::binarize;

  TTS_ULP_EQUAL( flx::derivative_1st(eve::binarize)(eve::is_ltz(a0), a1, a2), eve::zero(eve::as(a0)), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::binarize)(eve::is_ltz(a0), a1, a2), eve::zero(eve::as(a0)), 0.5);
};
