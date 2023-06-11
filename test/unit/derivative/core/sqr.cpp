//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sqr", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sqr)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sqr)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sqr
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sqr(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::sqr;
  using eve::detail::map;

  auto dsqr=[&](auto e) { return 2*e; };
  TTS_ULP_EQUAL( flx::derivative(eve::sqr)(a0), map(dsqr, a0), 0.5);
};
