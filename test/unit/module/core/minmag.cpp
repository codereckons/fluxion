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
TTS_CASE_TPL("Check return types of eve::minmag", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::minmag)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::minmag)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::minmag
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::minmag(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::minmag;
  using eve::detail::map;

  auto dminmag=[&](auto e) { return !!; }
  TTS_ULP_EQUAL( flx::diff(eve::minmag)(a0), map(dminmag, a0), 0.5);
};
