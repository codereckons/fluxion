//================================================================================================== //!
// Fluxion - Post-Modern Automatic Derivation                                                        //!
// Copyright : Fluxion Project Contributors                                                          //!
// SPDX-License-Identifier: BSL-1.0                                                                  //!
//================================================================================================== //!
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <flx/derivative/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::sinc", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sinc)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sinc)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sinc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinc(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinc;
  using eve::detail::map;

  auto dsinc = [&](auto x) { return eve::cos(x)/x - eve::sin(x)/eve::sqr(x); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::sinc)(a0), map(dsinc, a0), 70.0);
};
