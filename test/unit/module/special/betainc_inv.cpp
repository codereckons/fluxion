//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/special.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::betainc_inv", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::betainc_inv)(T(), T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::betainc_inv)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::betainc_inv
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::betainc_inv(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.1,1.0)
                           , tts::randoms(0.1,1.0)
                           , tts::randoms(0.1,1.0)
                           )
              )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::betainc_inv;
  using eve::detail::map;

  auto dbetainc_inv = [&]( auto e, auto f, auto g) { return eve::rec(flx::diff(eve::betainc)(eve::betainc_inv(e, f, g), f, g)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::betainc_inv)(a0, a1, a2), map(dbetainc_inv, a0, a1, a2), 50.0);
};
