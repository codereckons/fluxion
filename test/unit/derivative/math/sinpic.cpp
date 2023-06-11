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
TTS_CASE_TPL("Check return types of eve::sinpic", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::derivative(eve::sinpic)(T())  , T  );
  TTS_EXPR_IS( flx::derivative(eve::sinpic)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::sinpic
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::sinpic(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 10.0)
                           )
              )
<typename T>(T const& a0)
{
  using eve::sinpic;
  using eve::detail::map;

  auto dsinpic = [&](auto x) { return eve::cospi(x)/x - eve::sinpi(x)/(eve::pi(eve::as(x))*eve::sqr(x)); };
  TTS_ULP_EQUAL(flx::derivative_1st(eve::sinpic)(a0), map(dsinpic, a0), 30.0);
};
