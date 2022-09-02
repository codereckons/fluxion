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
TTS_CASE_TPL("Check return types of eve::inc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::inc)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::inc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::inc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::inc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::inc;
  using eve::detail::map;

  auto dinc=[&](auto e) { return eve::one(eve::as(e)); };
  TTS_ULP_EQUAL( flx::diff(eve::inc)(a0), map(dinc, a0), 0.5);
};
