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
TTS_CASE_TPL("Check return types of eve::omega", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(flx::diff(eve::omega)(T()), T);
  TTS_EXPR_IS(flx::diff(eve::omega)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::omega
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::omega(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::randoms(0.0,10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::omega;
  using eve::detail::map;
  using e_t = eve::element_type_t<T>;

  auto domega = [&](auto x) -> e_t{ return eve::omega(x)/eve::inc(omega(x)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::omega)(a0), map(domega, a0), 0.5);
};
