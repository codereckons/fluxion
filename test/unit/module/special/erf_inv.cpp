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
TTS_CASE_TPL("Check return types of eve::erf_inv", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::erf_inv)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::erf_inv)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::erf_inv
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::erf_inv(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,1.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::erf_inv;
  using eve::detail::map;

  auto derf_inv = [&]( auto e) { return eve::rec(flx::diff(eve::erf)(eve::erf_inv(e))); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::erf_inv)(a0), map(derf_inv, a0), 2.0);
};
