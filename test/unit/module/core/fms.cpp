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
TTS_CASE_TPL("Check return types of eve::fms", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::fms)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::fms)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::fms
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::fms(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::fms;
  using eve::detail::map;

  auto dfms=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::fms)(a0), map(dfms, a0), 0.5);
};
