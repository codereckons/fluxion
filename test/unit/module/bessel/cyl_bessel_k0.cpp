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
TTS_CASE_TPL("Check return types of eve::cyl_bessel_k0", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_k0)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::cyl_bessel_k0)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cyl_bessel_k0
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cyl_bessel_k0(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.2,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cyl_bessel_k0;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dcyl_bessel_k0 = [&](auto e) -> v_t{ return boost::math::cyl_bessel_k_prime(0, e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::cyl_bessel_k0)(a0), map(dcyl_bessel_k0, a0), 20.);
};
