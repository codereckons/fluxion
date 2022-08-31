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
TTS_CASE_TPL("Check return types of eve::sqr_abs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sqr_abs)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::sqr_abs)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqr_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqr_abs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::sqr_abs;
  using eve::detail::map;

  auto dsqr_abs=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::sqr_abs)(a0), map(dsqr_abs, a0), 0.5);
};
