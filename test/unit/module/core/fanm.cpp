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
TTS_CASE_TPL("Check return types of eve::fanm", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::fanm)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::fanm)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fanm
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fanm(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fanm;
  using eve::detail::map;

  auto dfanm1=[&](auto e, auto , auto ) { return eve::one(eve::as(e)); };
  auto dfanm2=[&](auto , auto , auto g) { return -g; };
  auto dfanm3=[&](auto , auto f, auto ) { return -f; };
  TTS_ULP_EQUAL( flx::diff_1st(eve::fanm)(a0, a1, a2), map(dfanm1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::fanm)(a0, a1, a2), map(dfanm2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::diff_3rd(eve::fanm)(a0, a1, a2), map(dfanm3, a0, a1, a2), 0.5);
};
