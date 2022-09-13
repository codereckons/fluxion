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
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_y1)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sph_bessel_y1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_y1(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sph_bessel_y1;
  using eve::detail::map;

  auto dsph_bessel_y1 = [&](auto e) { return boost::math::sph_neumann_prime(1u, e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sph_bessel_y1)(a0), map(dsph_bessel_y1, a0), 10);
};
