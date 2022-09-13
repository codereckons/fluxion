//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/bessel.hpp>
#include <boost/math/special_functions/airy.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::airy_ai", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::airy_ai)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::airy_ai)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::airy_ai
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::airy_ai(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0),
                             tts::randoms(-10.0,0.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::airy_ai;
  using eve::detail::map;

  auto dairy_ai = [&](auto e) { return boost::math::airy_ai_prime(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::airy_ai)(a0), map(dairy_ai, a0), 100);
  TTS_ULP_EQUAL(flx::diff_1st(eve::airy_ai)(a1), map(dairy_ai, a1), 100);
};
