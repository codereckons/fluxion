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
TTS_CASE_TPL("Check return types of eve::minus", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::minus)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::minus)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::minus
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::minus(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::minus;
  using eve::detail::map;

  auto dminus=[&](auto e) { return eve::mone(eve::as(e)); };
  TTS_ULP_EQUAL( flx::derivative(eve::minus)(a0), map(dminus, a0), 0.5);
};
