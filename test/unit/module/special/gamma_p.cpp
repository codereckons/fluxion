//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/special.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::gamma_p", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::gamma_p)(T(), T()), T);
  TTS_EXPR_IS(flx::diff(eve::gamma_p)(v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::gamma_p
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::gamma_p(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.1,10.0)
                           , tts::randoms(0.1,10.0)
                           )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::gamma_p;
  using eve::detail::map;

  auto dgamma_p = [&]( auto x, auto k) { return eve::exp(eve::dec(k) * eve::log(x) - x - eve::log_gamma(k)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::gamma_p)(a0, a1), map(dgamma_p, a0, a1), 2.0);
};
