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
TTS_CASE_TPL("Check return types of eve::clamp", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::clamp)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::clamp)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::clamp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::clamp(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10, 10),
                            tts::randoms(-15, 0),
                            tts::randoms(0, 15)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::clamp;
  using eve::detail::map;

  auto dclamp1=[&](auto e, auto f, auto g) { return flx::derivative_1st(eve::min)(eve::max(e, f), g)*flx::derivative_1st(eve::max)(e, f); };
  auto dclamp2=[&](auto e, auto f, auto g) { return flx::derivative_1st(eve::min)(eve::max(e, f), g)*flx::derivative_2nd(eve::max)(e, f);};
  auto dclamp3=[&](auto e, auto f, auto g) { return flx::derivative_2nd(eve::min)(eve::max(e, f), g); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::clamp)(a0, a1, a2), map(dclamp1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::clamp)(a0, a1, a2), map(dclamp2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::clamp)(a0, a1, a2), map(dclamp3, a0, a1, a2), 0.5);
};
