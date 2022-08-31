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
TTS_CASE_TPL("Check return types of eve::max", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::max)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::max)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::max
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::max(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::max;
  using eve::detail::map;

  auto dmax=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::max)(a0), map(dmax, a0), 0.5);
};
