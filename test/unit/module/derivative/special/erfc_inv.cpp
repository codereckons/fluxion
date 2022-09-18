//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/special.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::erfc_inv", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::erfc_inv)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::erfc_inv)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::erfc_inv
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::erfc_inv(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,1.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::erfc_inv;
  using eve::detail::map;

  auto derfc_inv = [&]( auto e) { return eve::rec(flx::derivative(eve::erfc)(eve::erfc_inv(e))); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::erfc_inv)(a0), map(derfc_inv, a0), 2.0);
};
