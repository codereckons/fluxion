//==================================================================================================
// Fluxion - Post-Modern Automatic Derivation
// Copyright : Fluxion Project Contributors
// SPDX-License-Identifier: BSL-1.0
//==================================================================================================
#include "test.hpp"

#include <flx/differential/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sqr", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sqr)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::sqr)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqr
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqr(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::sqr;
  using eve::detail::map;

  TTS_ULP_EQUAL( flx::diff(eve::sqr)(a0), map([&](auto e) { return 2*e; }, a0), 0.5);
};
