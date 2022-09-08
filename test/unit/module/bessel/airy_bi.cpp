//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::airy_bi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(i_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(I_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(i_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::airy_bi)(I_t(), v_t()), T);
};

//==================================================================================================
// Tests for eve::airy_bi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::airy_bi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(0.0,10.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0, T const & a1)
{
  using eve::airy_bi;
  using eve::detail::map;

  auto dairy_bi = [&](auto i, auto e, auto f) { return boost::math::airy_bi_prime(i, e, f); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::airy_bi)(i, a0, a1), map(dairy_bi, a0, a1), 0.5);
};
