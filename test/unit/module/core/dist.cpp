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
TTS_CASE_TPL("Check return types of eve::dist", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::dist)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::dist)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::dist
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::dist(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::dist;
  using eve::detail::map;

  auto ddist1=[&](auto e, auto f) { return eve::sign(e-f); };
  auto ddist2=[&](auto e, auto f) { return eve::sign(f-e); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::dist)(a0, a1), map(ddist1, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::dist)(a0, a1), map(ddist2, a0, a1), 0.5);
};
