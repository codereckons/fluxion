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
TTS_CASE_TPL("Check return types of eve::sph_bessel_jn", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_jn)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_jn)(v_t(), v_t()), v_t);
//   TTS_EXPR_IS(flx::diff(eve::sph_bessel_jn)(i_t(), T()), T);
   TTS_EXPR_IS(flx::diff(eve::sph_bessel_jn)(I_t(), T()), T);
   TTS_EXPR_IS(flx::diff(eve::sph_bessel_jn)(i_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sph_bessel_jn
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_jn(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                           , tts::randoms(eve::eps,10.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0)
{
  using eve::sph_bessel_jn;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dsph_bessel_jn = [&](auto i, auto e) -> v_t{ return boost::math::sph_bessel_prime(i, double(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sph_bessel_jn)(i, a0), map(dsph_bessel_jn, i, a0), 1300);
};
