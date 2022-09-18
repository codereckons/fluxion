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
TTS_CASE_TPL("Check return types of eve::sph_bessel_yn", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::derivative(eve::sph_bessel_yn)(T(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::sph_bessel_yn)(v_t(), v_t()), v_t);
//   TTS_EXPR_IS(flx::derivative(eve::sph_bessel_yn)(i_t(), T()), T);
   TTS_EXPR_IS(flx::derivative(eve::sph_bessel_yn)(I_t(), T()), T);
   TTS_EXPR_IS(flx::derivative(eve::sph_bessel_yn)(i_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sph_bessel_yn
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_yn(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                           , tts::randoms(eve::eps,10.0)
                           )
              )
<typename I,typename T>(I const & i,T const& a0)
{
  using eve::sph_bessel_yn;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dsph_bessel_yn = [&](auto i, auto e) -> v_t{ return boost::math::sph_neumann_prime(i, double(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::sph_bessel_yn)(i, a0), map(dsph_bessel_yn, i, a0), 1300);
};
