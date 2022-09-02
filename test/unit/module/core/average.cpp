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
TTS_CASE_TPL("Check return types of eve::average", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::average)(T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::average)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::average
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::average(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0, T const& a1)
{
  using eve::average;
  using eve::detail::map;

  auto daverage=[&](auto e, auto) { return eve::half(eve::as(e)); };
  TTS_ULP_EQUAL( flx::diff_1st(eve::average)(a0, a1), map(daverage, a0, a1), 0.5);
  TTS_ULP_EQUAL( flx::diff_2nd(eve::average)(a0, a1), map(daverage, a0, a1), 0.5);
};
