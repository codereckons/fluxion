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
TTS_CASE_TPL("Check return types of eve::cyl_bessel_kn", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(i_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(I_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(i_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_kn)(I_t(), v_t()), T);
};

//==================================================================================================
// Tests for eve::cyl_bessel_kn
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cyl_bessel_kn(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(0.0,10.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0, T const & a1)
{
  using eve::cyl_bessel_kn;
  using eve::detail::map;

  auto dcyl_bessel_kn = [&](auto i, auto e, auto f) { return boost::math::cyl_bessel_kn_prime(i, e, f); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::cyl_bessel_kn)(i, a0, a1), map(dcyl_bessel_kn, a0, a1), 0.5);
};
