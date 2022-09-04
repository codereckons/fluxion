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
TTS_CASE_TPL("Check return types of eve::expm1", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::expm1)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::expm1)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::expm1
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::expm1(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog)
                           )
              )
<typename T>(T const& a0)
{
  using eve::expm1;
  using eve::detail::map;

  auto dexpm1 = [&](auto e) { return eve::exp(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::expm1)(a0), map(dexpm1, a0), 2.0);
};
