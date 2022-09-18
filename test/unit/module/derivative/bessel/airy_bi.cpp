//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/bessel.hpp>
#include <boost/math/special_functions/airy.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::airy_bi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::airy_bi)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::airy_bi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::airy_bi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::airy_bi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0),
                             tts::randoms(-10.0,0.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::airy_bi;
  using eve::detail::map;

  auto dairy_bi = [&](auto e) { return boost::math::airy_bi_prime(e); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::airy_bi)(a0), map(dairy_bi, a0), 100);
  TTS_ULP_EQUAL(flx::derivative_1st(eve::airy_bi)(a1), map(dairy_bi, a1), 100);
};
