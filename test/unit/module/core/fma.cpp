//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::fma", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::fma)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::fma)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fma(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fma;
  using eve::detail::map;

  auto dfma1=[&](auto , auto f, auto ) { return f; };
  auto dfma2=[&](auto e , auto , auto ) { return e; };
  auto dfma3=[&](auto , auto , auto g) { return eve::one(eve::as(g)); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::fma)(a0, a1, a2), map(dfma1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::fma)(a0, a1, a2), map(dfma2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_3rd(eve::fma)(a0, a1, a2), map(dfma3, a0, a1, a2), 0.5);
};
