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
TTS_CASE_TPL("Check return types of eve::secpi", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::secpi)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::secpi)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::secpi
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::secpi(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::secpi;
  using eve::detail::map;

  auto dsecpi = [&](auto e) { return eve::pi(eve::as(e))*(eve::secpi(e)*eve::tanpi(e)); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::secpi)(a0), map(dsecpi, a0), 1.0);
};
