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
TTS_CASE_TPL("Check return types of eve::round", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::round)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::round)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::round
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::round(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::round;
  using eve::detail::map;

  auto dround=[&](auto e) {  return eve::zero(eve::as(e)); };
  TTS_ULP_EQUAL( flx::diff(eve::round)(a0), map(dround, a0), 0.5);
};
