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
TTS_CASE_TPL("Check return types of eve::fam", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::fam)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::fam)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fam
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fam(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fam;
  using eve::detail::map;

  auto dfam1=[&](auto e, auto , auto ) { return eve::one(eve::as(e)); };
  auto dfam2=[&](auto , auto , auto g) { return g; };
  auto dfam3=[&](auto , auto f, auto ) { return f; };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::fam)(a0, a1, a2), map(dfam1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::fam)(a0, a1, a2), map(dfam2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::fam)(a0, a1, a2), map(dfam3, a0, a1, a2), 0.5);
};
