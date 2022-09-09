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
TTS_CASE_TPL("Check return types of eve::cyl_bessel_yn", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using I_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_yn)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_yn)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_yn)(i_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_yn)(I_t(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_yn)(i_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cyl_bessel_yn
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cyl_bessel_yn(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::ramp(0)
                          , tts::randoms(5.0,10.0)
                           )
              )
<typename I,typename T>(I  i,T const& a0)
{

 using v_t = eve::element_type_t<T>;
 using eve::cyl_bessel_yn;
  using eve::detail::map;

//  i = eve::max(i, 8);
  auto dcyl_bessel_yn = [&](auto i, auto e)->v_t{ return boost::math::cyl_neumann_prime(i, double(e)); };
  TTS_RELATIVE_EQUAL(flx::diff_1st(eve::cyl_bessel_yn)(i, a0), map(dcyl_bessel_yn, i, a0), 1.0e-3);
};
