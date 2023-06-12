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
TTS_CASE_TPL("Check return types of eve::lerp", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::lerp)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::lerp)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::lerp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::lerp(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, 10),
                            tts::randoms(-15, 0),
                            tts::randoms(0, 1)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::lerp;
  using eve::detail::map;

  auto dlerp1=[&](auto , auto , auto t) { return eve::oneminus(t); };
  auto dlerp2=[&](auto , auto , auto t) { return t; };
  auto dlerp3=[&](auto e, auto f, auto ) { return f-e; };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::lerp)(a0, a1, a2), map(dlerp1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::lerp)(a0, a1, a2), map(dlerp2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::lerp)(a0, a1, a2), map(dlerp3, a0, a1, a2), 0.5);
};
