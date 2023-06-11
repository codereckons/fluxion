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
TTS_CASE_TPL("Check return types of eve::abs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::abs)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::abs)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::abs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::abs;
  using eve::detail::map;

  auto dabs=[&](auto e) { return eve::sign(e); };
  TTS_ULP_EQUAL( flx::derivative(eve::abs)(a0), map(dabs, a0), 0.5);
};
