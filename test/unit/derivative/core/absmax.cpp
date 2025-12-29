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
TTS_CASE_TPL("Check return types of eve::absmax", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::absmax)(T(), T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::absmax)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::absmax
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::absmax(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::absmax;
  using eve::detail::map;

  auto dabsmax1=[&](auto e, auto f) { return flx::derivative_1st(eve::max)(e, f)*eve::sign(e); };
  auto dabsmax2=[&](auto e, auto f) { return flx::derivative_2nd(eve::max)(e, f)*eve::sign(f); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::absmax)(a0, a1), map(dabsmax1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::absmax)(a0, a1), map(dabsmax2, a0, a1), 0.5);

  auto dabsmax3_1=[&](auto e, auto f, auto g) { return flx::derivative_1st(eve::max)(e, f, g)*eve::sign(e); };
  auto dabsmax3_2=[&](auto e, auto f, auto g) { return flx::derivative_2nd(eve::max)(e, f, g)*eve::sign(f); };
  auto dabsmax3_3=[&](auto e, auto f, auto g) { return flx::derivative_3rd(eve::max)(e, f, g)*eve::sign(g); };
  TTS_ULP_EQUAL( flx::derivative_1st(eve::absmax)(a0, a1, a2), map(dabsmax3_1, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_2nd(eve::absmax)(a0, a1, a2), map(dabsmax3_2, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( flx::derivative_3rd(eve::absmax)(a0, a1, a2), map(dabsmax3_3, a0, a1, a2), 0.5);
};
