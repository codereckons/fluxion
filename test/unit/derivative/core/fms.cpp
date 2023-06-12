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
TTS_CASE_TPL("Check return types of eve::fms", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::fms)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::fms)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fms
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fms(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fms;
  using eve::detail::map;

  auto dfms1=[&](auto , auto f, auto ) { return f; };
  auto dfms2=[&](auto e , auto , auto ) { return e; };
  auto dfms3=[&](auto , auto , auto g) { return eve::mone(eve::as(g)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::fms)(a0, a1, a2), map(dfms1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::fms)(a0, a1, a2), map(dfms2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::fms)(a0, a1, a2), map(dfms3, a0, a1, a2), 0.5);
};
