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
TTS_CASE_TPL("Check return types of eve::negabsmin", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::negabsmin)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::negabsmin)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::negabsmin
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::negabsmin(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::negabsmin;
  using eve::detail::map;

  auto dnegabsmin=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::negabsmin)(a0), map(dnegabsmin, a0), 0.5);
};
