//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <flx/differential/polynomial.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::reverse_horner", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::reverse_horner)(T(), T(), T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::reverse_horner)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// Tests for eve::reverse_horner
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::reverse_horner(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate( tts::between(0, 1.0)
                           , tts::between(2, 3.0)
                           , tts::between(5, 7.0)
                           , tts::between(1, 5.0)
                           , tts::between(-3, 2.0)
                           )
             )
<typename T>(T const& x, T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::reverse_horner;
  using eve::detail::map;
 auto dreverse_horner = [&](auto e, auto , auto c, auto b, auto a) { return c+2*b*e+3*a*e*e; };
  TTS_ULP_EQUAL(flx::diff_1st(eve::reverse_horner)(x, a3, a2, a1, a0), map(dreverse_horner, x, a3, a2, a1, a0), 0.5);
};
