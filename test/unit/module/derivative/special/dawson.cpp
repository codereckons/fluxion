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
TTS_CASE_TPL("Check return types of eve::dawson", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::dawson)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::dawson)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::dawson
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::dawson(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::dawson;
  using eve::detail::map;


  auto ddawson = [&](auto e) { return  eve::oneminus(2*e*dawson(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::dawson)(a0), map(ddawson, a0), 50);
};
