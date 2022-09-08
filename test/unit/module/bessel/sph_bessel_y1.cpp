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
TTS_CASE_TPL("Check return types of eve::sph_bessel_y1", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(i_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(I_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(i_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(I_t(), v_t()), T);
};

//==================================================================================================
// Tests for eve::sph_bessel_y1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_y1(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(0.0,10.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0, T const & a1)
{
  using eve::sph_bessel_y1;
  using eve::detail::map;

  auto dsph_bessel_y1 = [&](auto i, auto e, auto f) { return boost::math::sph_bessel_y1_prime(i, e, f); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sph_bessel_y1)(i, a0, a1), map(dsph_bessel_y1, a0, a1), 0.5);
};
