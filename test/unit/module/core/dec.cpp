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
TTS_CASE_TPL("Check return types of eve::dec", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::dec)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::dec)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::dec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::dec(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::dec;
  using eve::detail::map;

  auto ddec=[&](auto e) {return eve::one(eve::as(e)); };
  TTS_ULP_EQUAL( flx::diff(eve::dec)(a0), map(ddec, a0), 0.5);
};
