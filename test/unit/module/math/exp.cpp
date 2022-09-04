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
TTS_CASE_TPL("Check return types of eve::exp", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::exp)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::exp)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::exp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::exp(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog, eve::maxlog)
                           )
              )
<typename T>(T const& a0)
{
  using eve::exp;
  using eve::detail::map;

  auto dexp = [&](auto e) { return eve::exp(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::exp)(a0), map(dexp, a0), 1.0);
};
