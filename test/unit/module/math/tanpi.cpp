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
TTS_CASE_TPL("Check return types of eve::tanpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::tanpi)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::tanpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::tanpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::tanpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::tanpi;
  using eve::detail::map;

  auto dtanpi = [&](auto x) { return eve::pi(eve::as(x))*eve::sqr(eve::secpi(x)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::tanpi)(a0), map(dtanpi, a0), 10.0);
};
