//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/differential/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::exp10", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::exp10)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::exp10)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::exp10
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::exp10(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog10, eve::maxlog10)
                           )
              )
<typename T>(T a0)
{
  using eve::exp10;
  using eve::detail::map;

  auto dexp10 = [&](auto e) { return eve::exp10(e)*eve::log_10(eve::as(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::exp10)(a0), map(dexp10, a0), 2.0);
};
