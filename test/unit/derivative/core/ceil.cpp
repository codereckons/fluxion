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
TTS_CASE_TPL("Check return types of eve::ceil", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::ceil)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::ceil)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::ceil
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::ceil(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::ceil;
  using eve::detail::map;

  auto dceil=[&](auto e) { return eve::zero(eve::as(e)); }; 
  TTS_ULP_EQUAL( flx::derivative(eve::ceil)(a0), map(dceil, a0), 0.5);
};
