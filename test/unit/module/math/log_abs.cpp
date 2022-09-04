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
TTS_CASE_TPL("Check return types of eve::log_abs", flx::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( flx::diff(eve::log_abs)(T())  , T  );
  TTS_EXPR_IS( flx::diff(eve::log_abs)(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::log_abs
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::log_abs(eve::wide)",
              flx::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
              )
<typename T>(T const& a0)
{
  using eve::log_abs;
  using eve::detail::map;

  auto dlog_abs = [&](auto e) { return eve::rec(e); };
  TTS_ULP_EQUAL(flx::diff_1st(eve::log_abs)(a0), map(dlog_abs, a0), 1.0);
};
