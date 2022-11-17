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
TTS_CASE_TPL("Check return types of eve::rec", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::rec)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::rec)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::rec
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::rec(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::rec;
  using eve::detail::map;

  auto drec=[&](auto e) {  return -1/eve::sqr(e); };
  TTS_ULP_EQUAL( flx::derivative(eve::rec)(a0), map(drec, a0), 1.5);
};
