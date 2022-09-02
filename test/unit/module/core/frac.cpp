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
TTS_CASE_TPL("Check return types of eve::frac", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::frac)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::frac)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::frac
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::frac(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::frac;
  using eve::detail::map;

  auto dfrac=[&](auto e) {   return eve::one(eve::as(e)); };
  TTS_ULP_EQUAL( flx::diff(eve::frac)(a0), map(dfrac, a0), 0.5);
};
