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
TTS_CASE_TPL("Check return types of eve::cyl_bessel_in", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::derivative_2nd(eve::cyl_bessel_in)(T(), T()), T);
  TTS_EXPR_IS(flx::derivative_2nd(eve::cyl_bessel_in)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::derivative_2nd(eve::cyl_bessel_in)(i_t(), T()), T);
  TTS_EXPR_IS(flx::derivative_2nd(eve::cyl_bessel_in)(I_t(), T()), T);
  TTS_EXPR_IS(flx::derivative_2nd(eve::cyl_bessel_in)(i_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cyl_bessel_in
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cyl_bessel_in(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(2.0,5.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0)
{
  using eve::cyl_bessel_in;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dcyl_bessel_in = [&](auto i, auto e)-> v_t{ return boost::math::cyl_bessel_i_prime(i, double(e)); };
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::cyl_bessel_in)(i, a0), map(dcyl_bessel_in, i, a0), 1000);
};
