//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::cyl_bessel_jn", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::derivative(eve::cyl_bessel_jn)(T(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::cyl_bessel_jn)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::derivative(eve::cyl_bessel_jn)(i_t(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::cyl_bessel_jn)(I_t(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::cyl_bessel_jn)(i_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cyl_bessel_jn
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cyl_bessel_jn(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(0.0,10.0)
                           )
              )
<typename I,typename T>(I const & i0,T const& a0)
{
  using eve::cyl_bessel_jn;
  using eve::detail::map;

  auto dcyl_bessel_jn = [&](auto i, auto e) { return boost::math::cyl_bessel_j_prime(i, e); };
  TTS_RELATIVE_EQUAL(flx::derivative_1st(eve::cyl_bessel_jn)(i0, a0), map(dcyl_bessel_jn, i0, a0), 1.0e-4);
};
