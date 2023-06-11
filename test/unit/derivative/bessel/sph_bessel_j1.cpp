//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sph_bessel_j1", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(flx::derivative(eve::sph_bessel_j1)(T()), T);
  TTS_EXPR_IS(flx::derivative(eve::sph_bessel_j1)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sph_bessel_j1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sph_bessel_j1(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sph_bessel_j1;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto dsph_bessel_j1 = [&](auto e) ->v_t{ return boost::math::sph_bessel_prime(1, double(e)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::sph_bessel_j1)(a0), map(dsph_bessel_j1, a0), 80.0)
    << "-> " << std::setprecision(15) << a0 << '\n'
    << "-> " << "flx   " << flx::derivative_1st(eve::sph_bessel_j1)(a0)<< '\n'
    << "-> " << "boost " << map(dsph_bessel_j1, a0)<< '\n';
};
