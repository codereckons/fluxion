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
TTS_CASE_TPL("Check return types of eve::fsnm", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::fsnm)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::fsnm)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fsnm
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fsnm(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::fsnm;
  using eve::detail::map;

  auto dfsnm1=[&](auto e, auto , auto ) { return eve::mone(eve::as(e)); };
  auto dfsnm2=[&](auto , auto , auto g) { return -g; };
  auto dfsnm3=[&](auto , auto f, auto ) { return -f; };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::fsnm)(a0, a1, a2), map(dfsnm1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::fsnm)(a0, a1, a2), map(dfsnm2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::fsnm)(a0, a1, a2), map(dfsnm3, a0, a1, a2), 0.5);
};
