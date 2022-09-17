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
TTS_CASE_TPL("Check return types of eve::signgam", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::signgam)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::signgam)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::signgam
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::signgam(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::signgam;

  TTS_ULP_EQUAL(flx::derivative_1st(eve::signgam)(a0), eve::zero(eve::as(a0)), 0.5);
};
