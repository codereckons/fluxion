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
TTS_CASE_TPL("Check return types of eve::sinhc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::sinhc)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::sinhc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sinhc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinhc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinhc;
  using eve::detail::map;

  auto dsinhc = [&](auto x) { return eve::cosh(x)/x - eve::sinh(x)/eve::sqr(x); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::sinhc)(a0), map(dsinhc, a0), 70.0);
};
