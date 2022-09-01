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
TTS_CASE_TPL("Check return types of eve::fnma", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::fnma)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::fnma)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fnma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fnma(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fnma;
  using eve::detail::map;

  auto dfnma1=[&](auto , auto f, auto ) { return -f; };
  auto dfnma2=[&](auto e , auto , auto ) { return -e; };
  auto dfnma3=[&](auto , auto , auto g) { return eve::one(eve::as(g)); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::fnma)(a0, a1, a2), map(dfnma1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::fnma)(a0, a1, a2), map(dfnma2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_3rd(eve::fnma)(a0, a1, a2), map(dfnma3, a0, a1, a2), 0.5);
};
