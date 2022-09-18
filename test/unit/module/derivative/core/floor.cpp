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
TTS_CASE_TPL("Check return types of eve::floor", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::floor)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::floor)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::floor
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::floor(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::floor;
  using eve::detail::map;

  auto dfloor=[&](auto e) {  return eve::zero(eve::as(e)); };
  TTS_ULP_EQUAL( flx::derivative(eve::floor)(a0), map(dfloor, a0), 0.5);
};
