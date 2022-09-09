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
TTS_CASE_TPL("Check return types of eve::sph_bessel_j0", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(flx::diff(eve::sph_bessel_j0)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::sph_bessel_j0)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sph_bessel_j0
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_j0(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.2,10.0)
                           )
             )
<typename T>(T const& a0)
{
  using eve::sph_bessel_j0;
  using eve::detail::map;

  auto dsph_bessel_j0 = [&](auto e) { return boost::math::sph_bessel_prime(0, e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sph_bessel_j0)(a0), map(dsph_bessel_j0, a0), 250);
};
