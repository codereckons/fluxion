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
TTS_CASE_TPL("Check return types of eve::sub", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sub)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sub)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sub
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sub(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::sub;
  using eve::detail::map;

  auto dsub1=[&](auto e, auto ) { return eve::one(eve::as(e)); };
  auto dsub2=[&](auto , auto f) { return eve::mone(eve::as(f)); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::sub)(a0, a1), map(dsub1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::sub)(a0, a1), map(dsub2, a0, a1), 0.5);
};
