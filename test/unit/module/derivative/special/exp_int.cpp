//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/derivative/special.hpp>
#include <boost/math/special_functions/expint.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::exp_int", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::derivative(eve::exp_int)(T(), T()), T);
  TTS_EXPR_IS(flx::derivative(eve::exp_int)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::exp_int
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::exp_int(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::as_integer(tts::ramp(1))
                          ,    tts::randoms(0.0,10.0)
                           )
              )
<typename T, typename I>(I const& n, T const& a0)
{
  using eve::exp_int;
  using eve::detail::map;

  std::cout << eve::exp_int(n, a0) << std::endl;
  auto dexp_int = [&](auto n, auto e) { return -boost::math::expint((unsigned int)(n-1), e); };
  TTS_ULP_EQUAL(flx::derivative_2nd(eve::exp_int)(n, a0), map(dexp_int, n, a0), 5.0);
};
