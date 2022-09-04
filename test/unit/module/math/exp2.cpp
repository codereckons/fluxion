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
TTS_CASE_TPL("Check return types of eve::exp2", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::exp2)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::exp2)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::exp2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::exp2(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog2, eve::maxlog2)
                           )
              )
<typename T>(T a0)
{
  using eve::exp2;
  using eve::detail::map;

  auto dexp2 = [&](auto e) { return eve::exp2(e)*eve::log_2(eve::as(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::exp2)(a0), map(dexp2, a0), 2.0);
};
