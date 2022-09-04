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
TTS_CASE_TPL("Check return types of eve::cbrt", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::cbrt)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::cbrt)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::cbrt
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::cbrt(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::cbrt;
  using eve::detail::map;

  auto dcbrt = [&](auto e) { return eve::third(eve::as(e))*eve::sqr(eve::rec(eve::cbrt(e))); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::cbrt)(a0), map(dcbrt, a0), 2.0);
};
